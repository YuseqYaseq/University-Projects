#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <sstream>

/*#include "common.h"
#include "ConversionToGraph.h"
#include "FindPath.h"*/
const char block = '#';
const char diamond = '+';
const char bomb = '*';
const char pit = 'O';
const char vehicle = '.';
const char empty = ' ';


class Edge {
public:
    unsigned int direction;
    std::vector<int> diamonds_on_path;
};

class Node {
public:
    // list of (id, list_of_diamonds) tuples
    std::vector<std::pair<unsigned int, Edge>> neighbours;
};

class Graph {
public:
    std::vector<Node> nodes;
    int num_of_diamonds;

    Graph() {
        num_of_diamonds = 0;
    }
};
////////////

void visit_node(Graph& graph, const std::vector<std::string>& board, unsigned int x, unsigned int y,
                const std::map<std::pair<unsigned int, unsigned int>, unsigned int>& pos_to_diam_id,
                std::map<std::pair<unsigned int, unsigned int>, int>& pos_to_node_id,
                std::vector<std::vector<bool>>& visited, unsigned int& number_of_nodes);

void check_path(Graph& graph, const std::vector<std::string>& board, const unsigned int x, const unsigned int y,
                const std::map<std::pair<unsigned int, unsigned int>, unsigned int>& pos_to_diam_id,
                std::map<std::pair<unsigned int, unsigned int>, int>& pos_to_node_id,
                std::vector<std::vector<bool>>& visited, unsigned int& number_of_nodes,
                const int x_modifier, const int y_modifier, int direction) {
    if (board[y + y_modifier][x + x_modifier] == bomb || board[y + y_modifier][x + x_modifier] == block) {
        return;
    }
    Edge edge;
    bool path_finished = false;
    bool dead = false;
    std::pair<unsigned int, unsigned int> pos;
    for (unsigned int i = y + y_modifier, j = x + x_modifier;; i += y_modifier, j += x_modifier) {
        switch (board[i][j]) {
            case bomb:
                //leave this path
                path_finished = true;
                dead = true;
                break;
            case pit:
            case vehicle:
                path_finished = true;
                pos.first = i;
                pos.second = j;
                break;
            case diamond:
                edge.diamonds_on_path.push_back(pos_to_diam_id.at(std::make_pair(i, j)));
                break;
            case block:
                path_finished = true;
                pos.first = i - y_modifier;
                pos.second = j - x_modifier;
                break;
        }
        if (path_finished) {
            if (!dead) {
                //add new node
                if (!visited[pos.first][pos.second]) {
                    pos_to_node_id.insert(make_pair(pos, number_of_nodes));
                    graph.nodes.emplace_back(Node());
                    number_of_nodes++;
                }

                //add edge from current node to the new one
                edge.direction = direction;
                auto id = pos_to_node_id.at(std::make_pair(y, x));
                auto p = std::make_pair(pos_to_node_id.at(pos), edge);
                graph.nodes[id].neighbours.emplace_back(p);

                //run dfs on the new-found node
                if (!visited[pos.first][pos.second]) {
                    visited[pos.first][pos.second] = true;
                    visit_node(graph, board, pos.second, pos.first, pos_to_diam_id, pos_to_node_id, visited,
                               number_of_nodes);
                }
            }
            break;
        }
    }
}

void visit_node(Graph& graph, const std::vector<std::string>& board, const unsigned int x, const unsigned int y,
                const std::map<std::pair<unsigned int, unsigned int>, unsigned int>& pos_to_diam_id,
                std::map<std::pair<unsigned int, unsigned int>, int>& pos_to_node_id,
                std::vector<std::vector<bool>>& visited, unsigned int& number_of_nodes) {

    check_path(graph, board, x, y, pos_to_diam_id, pos_to_node_id, visited, number_of_nodes, 0, -1, 0);     // move 0
    check_path(graph, board, x, y, pos_to_diam_id, pos_to_node_id, visited, number_of_nodes, 1, -1, 1);     // move 1
    check_path(graph, board, x, y, pos_to_diam_id, pos_to_node_id, visited, number_of_nodes, 1, 0, 2);      // move 2
    check_path(graph, board, x, y, pos_to_diam_id, pos_to_node_id, visited, number_of_nodes, 1, 1, 3);      // move 3
    check_path(graph, board, x, y, pos_to_diam_id, pos_to_node_id, visited, number_of_nodes, 0, 1, 4);      // move 4
    check_path(graph, board, x, y, pos_to_diam_id, pos_to_node_id, visited, number_of_nodes, -1, 1, 5);     // move 5
    check_path(graph, board, x, y, pos_to_diam_id, pos_to_node_id, visited, number_of_nodes, -1, 0, 6);     // move 6
    check_path(graph, board, x, y, pos_to_diam_id, pos_to_node_id, visited, number_of_nodes, -1, -1, 7);    // move 7
}


Graph* generate_graph(unsigned int width, unsigned int height, std::vector<std::string> board) {

    auto graph = new Graph();
    std::map<std::pair<unsigned int, unsigned int>, unsigned int> pos_to_diam_id;
    unsigned int starting_x;
    unsigned int starting_y;

    //generate diamonds ids
    for(unsigned int i = 0; i < height; ++i) {
        for(unsigned int j = 0; j < width; ++j) {
            if(board[i][j] == diamond) {
                pos_to_diam_id.insert(std::make_pair(std::make_pair(i, j), graph->num_of_diamonds));
                graph->num_of_diamonds++;
            } else if(board[i][j] == vehicle) {
                starting_x = j;
                starting_y = i;
            }
        }
    }

    unsigned int number_of_nodes = 0;
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::map<std::pair<unsigned int, unsigned int>, int> pos_to_node_id;
    std::queue<std::pair<unsigned int, unsigned int>> nodes_to_visit;

    // perform dfs on the board
    graph->nodes.emplace_back(Node());
    visited[starting_y][starting_x] = true;
    pos_to_node_id.insert(std::make_pair(std::make_pair(starting_y, starting_x), number_of_nodes));
    number_of_nodes++;
    visit_node(*graph, board, starting_x, starting_y, pos_to_diam_id, pos_to_node_id, visited, number_of_nodes);
    return graph;
}
///////////

std::stack<unsigned int>* visit_node(const Graph& graph, std::vector<int>& diam_counter, const unsigned int node,
                                     const unsigned int moves_left, std::stack<unsigned int>& moves_stack) {
    if(moves_left == 0) {
        return nullptr;
    }
    auto& neighbours = graph.nodes[node].neighbours;
    for(unsigned int i = 0; i < neighbours.size(); ++i) {

        //add new diamonds
        for(unsigned int j = 0; j < neighbours[i].second.diamonds_on_path.size(); ++j) {
            diam_counter[neighbours[i].second.diamonds_on_path[j]]++;
        }
        moves_stack.push(neighbours[i].second.direction);

        //check if we didn't find solution
        bool found_solution = true;
        for(unsigned int j = 0; j < diam_counter.size(); ++j) {
            if(diam_counter[j] == 0) {
                found_solution = false;
                break;
            }
        }
        if(found_solution) {
            return &moves_stack;
        }
        auto result = visit_node(graph, diam_counter, neighbours[i].first, moves_left - 1, moves_stack);

        //if we found solution, return it
        if(result) return result;

        //else clear path
        for(unsigned int j = 0; j < neighbours[i].second.diamonds_on_path.size(); ++j) {
            diam_counter[neighbours[i].second.diamonds_on_path[j]]--;
        }
        moves_stack.pop();
    }

    //no neighbour was part of a solution so there is no solution
    return nullptr;
}

std::string find_path(Graph& graph, unsigned int max_moves) {
    if(max_moves > 2 * graph.nodes.size())
        max_moves = 2 * graph.nodes.size() + 4;
    std::vector<int> diam_counter(graph.num_of_diamonds, 0);
    std::stack<unsigned int> moves_stack;
    auto result = visit_node(graph, diam_counter, 0, max_moves, moves_stack);
    if(!result) return "BRAK";
    std::stringstream stream;
    while(!moves_stack.empty()) {
        stream << moves_stack.top();
        moves_stack.pop();
    }
    std::string solution = stream.str();
    std::reverse(solution.begin(), solution.end());
    return solution;
}
/////




int main() {
    std::vector<std::string> board;
    unsigned int width;
    unsigned int height;
    unsigned int max_moves;

    std::cin >> height >> width >> max_moves;
    board.resize(height);

    std::cin.ignore();
    for(int i = 0; i < height; ++i) {
            getline(std::cin, board[i]);
    }

    Graph* graph = generate_graph(width, height, board);
    std::string results = find_path(*graph, max_moves);
    std::cout << results << std::endl;
    delete graph;
    return 0;
}