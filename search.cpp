#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include "graph.h"
#include "node.h"
#include "search.h"
#include "comparison.h"

// Uniform Cost Search Implementation:
Search::Search(const Graph &graph) : graph(graph) {}

std::vector<std::string> Search::ucs(const std::string &start_stack, const std::string &goal_stack) {
    std::unordered_set<std::string> visited;
    std::priority_queue<const Node*, std::vector<const Node*>, comparison_class> to_visit;
    std::unordered_map<std::string, std::string> came_from;
    std::unordered_map<std::string, int> cost_so_far;

    const Node* start_node = graph.return_node(start_stack);
    start_node->set_total_cost(0);
    start_node->set_flips(0);

    // Track nodes to visit next
    to_visit.push(start_node);

    // Track visited nodes
    visited.insert(start_stack);

    // Track the previous node in the path
    came_from[start_stack] = "";

    // Track cost to reach a node
    cost_so_far[start_stack] = 0;

    int nodes_explored{};

    while (!to_visit.empty()) 
    {
        // Pop node from frontier with current minimum cost
        const Node* current = to_visit.top();
        to_visit.pop();

        nodes_explored++;

        // If node contains the goal state
        if (current->get_stack() == goal_stack) 
        {
            // Push path into vector
            std::vector<std::string> path;
            for (std::string at = goal_stack; !at.empty(); at = came_from[at]) 
            {
                path.push_back(at);
            }

            std::reverse(path.begin(), path.end());

            // Print cost to reach goal node
            std::cout << "Cost (number of flips to reach goal) is: " 
                << current->get_total_cost() << std::endl;
            std::cout << "Total number of nodes explored to reach goal is: "
                << nodes_explored << std::endl;

            // Return path
            return path;
        }

        // If node does not contain goal state, explore children
        for (const Node &neighbor : graph.get_neighbors(current->get_stack())) 
        {
            std::string neighbor_stack = neighbor.get_stack();
            int new_cost = cost_so_far[current->get_stack()] + 1;

            // If child is not visited, or child was visited with a higher cost path
            if (visited.find(neighbor_stack) == visited.end() || new_cost < cost_so_far[neighbor_stack]) 
            {
                // Update cost to child
                cost_so_far[neighbor_stack] = new_cost;

                // Push node with updated total cost into frontier
                const Node* neighbor_stack_node = graph.return_node(neighbor_stack);
                neighbor_stack_node->set_total_cost(new_cost);
                neighbor_stack_node->set_flips(new_cost);
                to_visit.push(neighbor_stack_node);
                visited.insert(neighbor_stack);

                // Update path to child
                came_from[neighbor_stack] = current->get_stack();
            }
        }
    }

    return {};
}

// A* Implementation:
std::vector<std::string> Search::a_star(const std::string &start_stack, const std::string &goal_stack) {
    // Tracks nodes already visited
    std::unordered_set<std::string> visited;

    // Tracks frontier - nodes to visit
    std::priority_queue<const Node*, std::vector<const Node*>, comparison_class> to_visit;

    // Tracks path to node
    std::unordered_map<std::string, std::string> came_from;

    // Tracks total number of flips to goal
    std::unordered_map<std::string, int> g_cost;

    const Node* start_node = graph.return_node(start_stack);
    start_node->set_flips(0);
    start_node->set_total_cost(start_node->get_non_adjacencies());

    to_visit.push(start_node);
    visited.insert(start_stack);
    came_from[start_stack] = "";
    g_cost[start_stack] = 0;

    int nodes_explored{};

    while (!to_visit.empty()) 
    {
        const Node* current = to_visit.top();
        to_visit.pop();

        nodes_explored++;

        // If node contains the goal state
        if (current->get_stack() == goal_stack) 
        {
            // Push path into vector
            std::vector<std::string> path;
            for (std::string at = goal_stack; !at.empty(); at = came_from[at]) 
            {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            std::cout << "Forward cost (number of flips to reach goal) is: " 
                << g_cost[goal_stack] << std::endl;
            std::cout << "Heuristic cost (number of non-adjacencies) in goal is: "
                << current->get_non_adjacencies() << std::endl;
            std::cout << "Total number of nodes explored to reach goal is: "
                << nodes_explored << std::endl;
            return path;
        }

        // If node does not contain goal state, explore children
        for (const Node &neighbor : graph.get_neighbors(current->get_stack())) 
        {
            std::string neighbor_stack = neighbor.get_stack();
            int new_g_cost = g_cost[current->get_stack()] + 1;

            // If child is not visited, or child was visited with a higher cost
            if (visited.find(neighbor_stack) == visited.end() || new_g_cost < g_cost[neighbor_stack]) 
            {
                // Update cost to child
                g_cost[neighbor_stack] = new_g_cost;

                int f_cost = new_g_cost + neighbor.get_non_adjacencies();

                const Node* neighbor_stack_node = graph.return_node(neighbor_stack);
                neighbor_stack_node->set_flips(new_g_cost);

                // Update toal cost
                neighbor_stack_node->set_total_cost(f_cost);

                to_visit.push(neighbor_stack_node);
                visited.insert(neighbor_stack);

                // Update path to child
                came_from[neighbor_stack] = current->get_stack();
            }
        }
    }

    return {};
}
