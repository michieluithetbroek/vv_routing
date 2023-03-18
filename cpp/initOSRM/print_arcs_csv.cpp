//
//  print_arcs_csv.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 18/03/2023.
//

#include "./initOSRM.ih"

void InitOSRM::print_arcs_csv() const
{
    ofstream output_file ("/Users/michiel/Documents/github/vv_routing/cpp/data/arcs.csv");
    
    output_file << " idx_from idx_to tile_x_from tile_y_from "
                << "tile_x_to tile_y_to distance time\n";

    for (Arc const &a: d_arcs)
        output_file << a;
}
