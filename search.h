#ifndef __SEARCH__
#define __SEARCH__

#include "graph.h"
#include "node.h"
#include <queue>
#include <unordered_set>
#include <vector>

class Search {
public:
    Search(const Graph &graph);

    std::vector<std::string> a_star(const std::string &start_stack, const std::string &goal_stack);
    std::vector<std::string> ucs(const std::string &start_stack, const std::string &goal_stack);

private:
    const Graph &graph;
};

#endif
