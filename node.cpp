#include "node.h"
#include <algorithm>
#include <cmath>

// Constructor definitions
Node::Node() : flips(0), non_adjacencies(0), total_cost(0) {}

Node::Node(const std::string &initial_stack) : stack(initial_stack), flips(0), total_cost(0) 
{
    calculate_non_adjacencies();
}

// Mutator definitions
void Node::set_stack(const std::string &new_stack) 
{
    stack = new_stack;
    calculate_non_adjacencies();
}

void Node::set_flips(const int num_flips) const
{
    const_cast<Node*>(this)->flips = num_flips;
}

void Node::set_non_adjacencies(const int num_non_adjacencies) 
{
    non_adjacencies = num_non_adjacencies;
}

void Node::set_total_cost(const int cost) const
{
    const_cast<Node*>(this)->total_cost = cost;
}

// Accessor definitions
std::string Node::get_stack() const 
{
    return stack;
}

int Node::get_flips() const {
    return flips;
}

int Node::get_non_adjacencies() const {
    return non_adjacencies;
}

int Node::get_total_cost() const {
    return total_cost;
}

// Calculate the number of non-adjacencies
void Node::calculate_non_adjacencies() 
{
    non_adjacencies = 0;
    for (size_t i = 1; i < stack.size(); ++i) 
    {
        if (std::abs(stack[i] - stack[i - 1]) != 1) 
        {
            non_adjacencies++;
        }
    }
}