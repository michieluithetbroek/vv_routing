//
//  initOSM.h
//  vv_routing
//
//  Created by Michiel uit het Broek on 12/03/2023.
//
// This class handles reading OSM files and translates them into a vector of
// Nodes. Nodes have a unique index (ranging from 0 to n) and describe their coordinate and
// corresponding tile.

#pragma once

#include <vector>
#include <string>

struct Node
{
    size_t idx_node;
    size_t idx_way;
    
    double lon;
    double lat;
    
    int tile_x;
    int tile_y;
    
    // Define constructors
    
    Node() = default;
    
    Node(size_t const idx_node,
         size_t const idx_way,
         double const lon,
         double const lat,
         int    const tile_x,
         int    const tile_y)
    :
      idx_node (idx_node),
      idx_way  (idx_way),
      lon      (lon),
      lat      (lat),
      tile_x   (tile_x),
      tile_y   (tile_y)
    { }
    
    // Allow to compare nodes on their index
    
    bool operator<(Node const &other) const
    {
        return idx_node < other.idx_node;
    };
    
    bool operator==(Node const &other) const
    {
        return idx_node == other.idx_node;
    };
};


class InitOSM
{
    std::vector<Node> d_nodes;
    
public:
    
    InitOSM(std::string const fileName = "/Users/michiel/Dropbox/programming/OSM_data/Groningen/groningen-latest.osm.pbf");
    
    void print_nodes() const;
    
private:
    
    void nodes_make_unique();
    void nodes_reindex();
};
