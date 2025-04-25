#ifndef __NODE__
#define __NODE__

#include <iostream>
#include <string>
#include <vector>

class Node {
public:
    // Constructors 
    Node();
    Node(const std::string &stack);

    // Mutators
    void set_stack(const std::string &);
    void set_flips(const int num_flips) const;
    void set_non_adjacencies(const int num_non_adjacencies);
    void set_total_cost(const int cost) const;

    // Accessors
    std::string get_stack() const;
    int get_flips() const;
    int get_non_adjacencies() const;
    int get_total_cost() const;

    // Methods
    void calculate_non_adjacencies();

    // Operator for priority queue
    bool operator<(const Node &other) const;

private:
    std::string stack;
    int flips;
    int non_adjacencies;
    int total_cost;
};

#endif
