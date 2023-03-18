//
//  print_arcs_terminal.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 18/03/2023.
//

#include "./initOSRM.ih"

void InitOSRM::print_arcs_terminal() const
{
    for (Arc const &a: d_arcs)
        cout << a;
}
