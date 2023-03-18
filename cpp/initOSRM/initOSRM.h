//
//  initOSRM.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/03/2023.
//

#pragma once

#include <vector>

#include "./../structs/node.h"
#include "./../structs/arc.h"

class InitOSRM
{
    std::vector<Node> d_nodes;
    std::vector<Arc>  d_arcs;
    
public:
    
    InitOSRM();
    
    void print_arcs_csv() const;
    void print_arcs_terminal() const;
    
private:
    void read_nodes_csv();
    
    void remove_redundant_nodes(int const threshold = 0);

};
