//
//  solver_GTSP.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 18/03/2023.
//

#pragma once

#include <vector>

#include "./../structs/node.h"
#include "./../structs/arc.h"

class Solver_GTSP
{
    std::vector<Node> d_nodes;
    std::vector<Arc>  d_arcs;
    
public:
    Solver_GTSP();
    
private:
    
    
};
