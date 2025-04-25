#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include "graph.h"
#include "node.h"
#include "search.h"

#ifndef COMPARISON_CLASS_H
#define COMPARISON_CLASS_H

#include "node.h"

class comparison_class {
public:
    bool operator()(const Node* first, const Node* second) const 
    {
        return first->get_total_cost() > second->get_total_cost();
    }
};

#endif