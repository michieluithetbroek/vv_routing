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
    
    output_file << fixed << setprecision(10)
                << "idx_way; idx_node_OSM; idx_node; lon; lat; tile_x; tile_y; way_type\n";

    
    for (Node const &n: d_nodes)
        output_file << setw(10) << n.idx_way      << ' '
                    << setw(10) << n.idx_node_OSM << ' '
                    << setw(10) << n.idx_node     << ' '
                    << setw(15) << n.lon          << ' '
                    << setw(15) << n.lat          << ' '
                    << setw(10) << n.tile_x       << ' '
                    << setw(10) << n.tile_y       << ' '
                    << setw(20) << n.way_type     << '\n';
}
