//
//  print_nodes_csv.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 13/03/2023.
//

#include "initOSM.ih"

void InitOSM::print_nodes_csv() const
{
    ofstream output_file ("/Users/michiel/Documents/github/vv_routing/cpp/data/nodes.csv");
    
    output_file << fixed << setprecision(4)
                << "idx_way;idx_node_OSM;idx_node;lon;lat;tile_x;tile_y\n";

    
    for (Node const &n: d_nodes)
        output_file << n.idx_way      << ';'
                    << n.idx_node_OSM << ';'
                    << n.idx_node     << ';'
                    << n.lon          << ';'
                    << n.lat          << ';'
                    << n.tile_x       << ';'
                    << n.tile_y       << '\n';
}
