//
//  initOSRM.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/03/2023.
//

#pragma once

#include <vector>

#include "./../structs/node.h"

class InitOSRM
{
    
    std::vector<Node> d_nodes;
    
public:
    
    InitOSRM();
    
private:
    void read_nodes_csv();

};
