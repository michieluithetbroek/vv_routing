//
//  read_arcs.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 18/03/2023.
//
// Only arcs for which both the from and to node are present
// in d_nodes are kept.
//

#include "./solver_GTSP.ih"

void Solver_GTSP::read_arcs(int const in_tile_x, int const in_tile_y, int const threshold)
{
    int const inst_tile_x1 = in_tile_x - threshold;
    int const inst_tile_y1 = in_tile_y - threshold;
    int const inst_tile_x2 = in_tile_x + threshold;
    int const inst_tile_y2 = in_tile_y + threshold;
    
    ifstream input_file ("/Users/michiel/Documents/github/vv_routing/cpp/data/arcs.csv");
    
    if (!input_file.is_open())
        throw string("Input arc file not found");
    
    // skip first line
    
    string line;
    getline(input_file, line);
    
    // Process all arc data
    
    int idx_from;
    int idx_to;
    int tile_x_from;
    int tile_y_from;
    int tile_x_to;
    int tile_y_to;
    
    double distance;
    double time;
    
    while (getline(input_file, line))
    {
        stringstream ss(line);
        
        ss >> idx_from
           >> idx_to
           >> tile_x_from
           >> tile_y_from
           >> tile_x_to
           >> tile_y_to
           >> distance
           >> time;
        
        if (tile_x_from < inst_tile_x1 or tile_x_from > inst_tile_x2)
            continue;
        
        if (tile_y_from < inst_tile_y1 or tile_y_from > inst_tile_y2)
            continue;
        
        if (tile_x_to < inst_tile_x1 or tile_x_to > inst_tile_x2)
            continue;
        
        if (tile_y_to < inst_tile_y1 or tile_y_to > inst_tile_y2)
            continue;
        
        d_arcs.emplace_back(idx_from, idx_to, tile_x_from, tile_y_from, tile_x_to, tile_y_to, distance, time);
    }
    
    d_nodes.shrink_to_fit();
    
    cout << "\nRead " <<  d_arcs.size() << " arcs for\n"
         << "  x: " << inst_tile_x1 << " " << inst_tile_x2 << '\n'
         << "  y: " << inst_tile_y1 << " " << inst_tile_y2 << endl;
}
