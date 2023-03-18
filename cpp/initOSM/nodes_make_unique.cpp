//
//  nodes_make_unique.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 12/03/2023.
//
// In OSM, nodes can be part of multiple ways. As a result
// we may have duplicate nodes which we delete here.

#include "initOSM.ih"

void InitOSM::nodes_make_unique()
{
    std::sort(begin(d_nodes), end(d_nodes));
    
    auto ip = unique(begin(d_nodes), end(d_nodes));
    
    d_nodes.resize(std::distance(begin(d_nodes), ip));
    d_nodes.shrink_to_fit();
}
