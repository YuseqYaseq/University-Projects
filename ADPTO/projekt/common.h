//
// Created by Joseph on 20.06.2019.
//

#ifndef PROJEKT_COMMON_H
#define PROJEKT_COMMON_H

#include <vector>

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

#endif //PROJEKT_COMMON_H
