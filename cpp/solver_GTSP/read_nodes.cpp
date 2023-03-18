//
//  read_nodes.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 18/03/2023.
//
// Read nodes from given input file. Only nodes located in the box
// described by a single tile and maximum distance from this tile.

#include "./solver_GTSP.ih"

void Solver_GTSP::read_nodes(int const in_tile_x, int const in_tile_y, int const threshold)
{
    int const inst_tile_x1 = in_tile_x - threshold;
    int const inst_tile_y1 = in_tile_y - threshold;
    int const inst_tile_x2 = in_tile_x + threshold;
    int const inst_tile_y2 = in_tile_y + threshold;
    
    // TODO move this functionallity to a class dedicated to reading/printing nodes
    
    ifstream input_file ("/Users/michiel/Documents/github/vv_routing/cpp/data/nodes.csv");
    
    if (!input_file.is_open())
        throw string("Input node file not found");
    
    size_t idx_node;
    size_t idx_way;

    unsigned long long idx_node_OSM;

    double lon;
    double lat;

    int tile_x;
    int tile_y;

    std::string way_type;
    
    // skip first line
    getline(input_file, way_type);
    
    string line;
    
    while (getline(input_file, line))
    {
        stringstream ss(line);
        
        ss >> idx_way
           >> idx_node_OSM
           >> idx_node
           >> lon
           >> lat
           >> tile_x
           >> tile_y
           >> way_type;
        
        if (tile_x < inst_tile_x1 or tile_x > inst_tile_x2)
            continue;
        
        if (tile_y < inst_tile_y1 or tile_y > inst_tile_y2)
            continue;
        
        d_nodes.emplace_back(idx_node, idx_way, idx_node_OSM, lon, lat, tile_x, tile_y, way_type);
    }
    
    d_nodes.shrink_to_fit();
    
    cout << "Read " <<  d_nodes.size() << " nodes for\n"
         << "  x: " << inst_tile_x1 << " " << inst_tile_x2 << '\n'
         << "  y: " << inst_tile_y1 << " " << inst_tile_y2 << endl;
}
