#include <iostream>
#include "graph.h"
#include "search.h"

// Function to generate all possible flips of a given string
std::vector<std::string> generate_flips(const std::string &str) 
{
    std::vector<std::string> flips;
    for (size_t i = 1; i < str.length(); ++i) 
    {
        std::string flipped = str;
        std::reverse(flipped.begin(), flipped.begin() + i + 1);
        flips.push_back(flipped);
    }
    return flips;
}

bool validate_input(std::string &str)
{
    if (str.length() > 11)
        return false;
    if (str.length() == 1 && str[0] >= 49 && str[0] <= 57)
        return true;
    if (str.length() == 1)
        return false;

    // If string has number '10', convert it to character ':'
    for (unsigned long i = 1; i < str.length(); i++)
    {
        if (str[i] == '0' && str[i-1] == '1')
        {
            str[i-1] = ':';
            str.erase(i, 1);
            i--;
        }
    }

    return true;
}

int main(void) {

    Graph graph;

    bool valid_input = false;
    //635149728
    std::string str{};
    std::string original_str{};

    while (!valid_input)
    {
        
        std::cout << "Enter a pancakes stack in order (left-> right = top->bottom). Enter 1-10 pancakes.\n";
        std::cout << "Pancakes should be listed consecutively, with no spaces or other characters (e.g. 63514972810)\n";
        std::cin >> str;

        // Create copy of string
        original_str = str;
    
        valid_input = validate_input(str);
        if (!valid_input)
            std::cout << "Invalid input. Please try again.\n\n";
    }

    // Create goal stack
    std::string goal_str = str;
    std::sort(goal_str.begin(), goal_str.end());

    if (goal_str.length() > 1) 
    {
        for (unsigned long i = 1; i < goal_str.length(); i++) 
        {
            if (goal_str[i] != goal_str[i-1] + 1) 
            {
                std::cerr << "Invalid input. Must contain all numbers in range 1...N, where N is the greatest number entered." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    int search_selection{};
    std::cout << "Select type of search to perform. Enter 1 for Uniform Cost Search. Enter 2 for A* Search\n";
    std::cin >> search_selection;

    // Add the initial node
    graph.add_node(str);

    // Generate and add all possible flips
    std::queue<std::string> to_process;
    std::unordered_set<std::string> visited;

    to_process.push(str);
    visited.insert(str);

    // Generate graph
    while (!to_process.empty()) 
    {
        std::string current = to_process.front();
        to_process.pop();

        std::vector<std::string> flips = generate_flips(current);
        for (const std::string &flip : flips) 
        {
            // Add flip permutation, if not already added to graph
            if (visited.find(flip) == visited.end()) 
            {
                graph.add_node(flip);
                to_process.push(flip);
                visited.insert(flip);
            }
            graph.add_edge(current, flip);
        }
    }

    // Vector to track path to goal node
    std::vector<std::string> path;

    // Perform Search
    Search search(graph);
    if (search_selection == 1)
        path = search.ucs(str, goal_str);
    else if (search_selection == 2)
        path = search.a_star(str, goal_str);
    else
    {
        std::cerr << "Invalid input. Must be a 1 for UCS and 2 for A*." << std::endl;
                exit(EXIT_FAILURE);
    }

    // Save flips and non_adjacencies for each node in path
    std::vector<int> flips_array;
    std::vector<int> non_adjacencies_array;
    for (const std::string &stack : path) 
    {
        const Node* current_node = graph.return_node(stack);
        flips_array.push_back(current_node->get_flips());
        non_adjacencies_array.push_back(current_node->get_non_adjacencies());
    }

    // Turn ':' back into "10" in the path
    for (auto& str : path) 
    {
        for (size_t i = 0; i < str.size(); ++i) 
        {
            if (str[i] == ':') 
            {
                str.insert(i, 1, '1');
                str[i + 1] = '0';
                ++i;
            }
        }
    }
    for (unsigned long i = 0; i < goal_str.length(); i++)
    {
        if (goal_str[i] == ':')
        {
            goal_str[i] = '1';
            goal_str.append("0");
        }
    }

    // Print the path
    if (!path.empty() && search_selection == 2) 
    {
        std::cout << "Path from " << original_str << " to " << goal_str << ": ";
        for (const std::string &stack : path) 
        {
            std::cout << stack << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Breakdown of nodes on path and their costs: " << std::endl;

        int i = 0;
        for (const std::string &stack : path) 
        {
            std::cout << "Stack: " << stack << "    Non-adjacencies:" <<
             non_adjacencies_array[i] <<
             "  Flips to reach: " << flips_array[i] <<
             "\n";
             i++;
        }
    } 
    else if (!path.empty() && search_selection == 1)
    {
        std::cout << "Path from " << original_str << " to " << goal_str << ": ";
        for (const std::string &stack : path) 
        {
            std::cout << stack << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Breakdown of nodes on path and their costs: " << std::endl;

        int i = 0;
        for (const std::string &stack : path) 
        {
            std::cout << "Stack: " << stack <<
             "  Flips to reach: " << flips_array[i] <<
             "\n";
             i++;
        }
    }
    else 
    {
        std::cout << "No path found from " << original_str << " to " << goal_str << std::endl;
    }

    return 0;
}
