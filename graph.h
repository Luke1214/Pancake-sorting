#ifndef __GRAPH__
#define __GRAPH__

#include "node.h"
#include <unordered_map>
#include <vector>

class Graph {
public:
    // Constructor
    Graph();

    // Methods
    void add_node(const std::string &stack);
    void add_edge(const std::string &stack1, const std::string &stack2);

    // Accessors
    const std::vector<Node>& get_neighbors(const std::string &stack) const;
    Node* return_node(const std::string &stack) const;

private:
    std::unordered_map<std::string, Node> nodes;
    std::unordered_map<std::string, std::vector<Node>> adjacency_list;
};

#endif
