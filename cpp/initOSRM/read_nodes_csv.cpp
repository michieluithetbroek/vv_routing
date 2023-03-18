//
//  read_nodes_csv.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/03/2023.
//
// Reads a file with nodes and stores this into the data member d_nodes.
//
// TODO can this be a function of the Node struct?

#include "./initOSRM.ih"

void InitOSRM::read_nodes_csv()
{
    // TODO better if the file location is not hardcoded..
    
    ifstream input_file ("/Users/michiel/Documents/github/vv_routing/cpp/data/nodes.csv");
    
    if (!input_file.is_open())
        throw string("Input file not found");
    
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
        
        d_nodes.emplace_back(idx_node, idx_way, idx_node_OSM, lon, lat, tile_x, tile_y, way_type);
    }
    
    d_nodes.shrink_to_fit();
}
