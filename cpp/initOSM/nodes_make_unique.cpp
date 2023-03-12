//
//  nodes_make_unique.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 12/03/2023.
//
// Remove duplicate nodes

#include "initOSM.ih"

void InitOSM::nodes_make_unique()
{
    std::sort(begin(d_nodes), end(d_nodes));
    
    auto ip = unique(begin(d_nodes), end(d_nodes));
    
    d_nodes.resize(std::distance(begin(d_nodes), ip));
    d_nodes.shrink_to_fit();
}
