//
//  print_nodes.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 12/03/2023.
//

#include "initOSM.ih"

void InitOSM::print_nodes() const
{
    cout << fixed << setprecision(4);

    for (Node const &n: d_nodes)
        cout << setw(15) << n.idx_way
             << setw(15) << n.idx_node_OSM
             << setw(10) << n.idx_node
             << setw(10) << n.lon
             << setw(10) << n.lat
             << setw(8)  << n.tile_x
             << setw(8)  << n.tile_y
             << setw(15) << n.way_type << '\n';
}
