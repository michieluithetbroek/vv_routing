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
    
    output_file << " idx_way idx_node_OSM idx_node lon lat tile_x tile_y way_type\n";
    
    for (Node const &node: d_nodes)
        output_file << node;
}
