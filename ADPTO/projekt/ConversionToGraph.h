//
// Created by Joseph on 20.06.2019.
//

#ifndef PROJEKT_CONVERSIONTOGRAPH_H
#define PROJEKT_CONVERSIONTOGRAPH_H

#include <vector>
#include <string>

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
            case vehicle:
            case pit:
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


#endif //PROJEKT_CONVERSIONTOGRAPH_H
