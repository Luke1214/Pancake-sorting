#include "graph.h"

// Constructor definition
Graph::Graph() {}

// Add a node to the graph
void Graph::add_node(const std::string &stack) 
{
    if (nodes.find(stack) == nodes.end()) 
    {
        Node new_node(stack);
        new_node.set_flips(0);

        int non_adj_count = 0;
        if (stack.length() <= 1)
        {
            ;
        }
        else
        {
            for (size_t i = 1; i < stack.length(); i++)
            {
                int first = (int)stack[i-1];
                int second = (int)stack[i];
                if (first != second+1 && first != second-1)
                {
                    non_adj_count++;
                }
            }
        }

        // std::cout << "The number of non-adjacencies for " << stack << " is: " << non_adj_count << std::endl;

        new_node.set_non_adjacencies(non_adj_count);

        nodes[stack] = new_node;
        adjacency_list[stack] = std::vector<Node>();
    }
}

// Return the node for the provided string
Node* Graph::return_node(const std::string &stack) const
{
    auto it = nodes.find(stack);
    if (it != nodes.end()) 
    {
        return const_cast<Node*>(&(it->second));
    } 
    else 
    {
        return nullptr;
    }
}


// Add an edge between two nodes in the graph
void Graph::add_edge(const std::string &stack1, const std::string &stack2) 
{
    if (nodes.find(stack1) != nodes.end() && nodes.find(stack2) != nodes.end()) 
    {
        adjacency_list[stack1].push_back(nodes[stack2]);
    }
}

// Get the neighbors of a node
const std::vector<Node>& Graph::get_neighbors(const std::string &stack) const 
{
    static std::vector<Node> empty_vector;
    auto it = adjacency_list.find(stack);
    if (it != adjacency_list.end()) 
    {
        return it->second;
    } 
    else 
    {
        return empty_vector;
    }
}
