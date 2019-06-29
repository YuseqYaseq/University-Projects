//
// Created by Joseph on 20.06.2019.
//

#ifndef PROJEKT_FINDPATH_H
#define PROJEKT_FINDPATH_H

#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <algorithm>
#include "common.h"

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

#endif //PROJEKT_FINDPATH_H
