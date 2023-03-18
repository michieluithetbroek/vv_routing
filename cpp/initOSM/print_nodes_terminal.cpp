//
//  print_nodes.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 12/03/2023.
//

#include "initOSM.ih"

void InitOSM::print_nodes_terminal() const
{
    for (Node const &node: d_nodes)
        cout << node;
}
