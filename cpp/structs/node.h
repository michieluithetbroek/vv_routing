//
//  node.h
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/03/2023.
//

#pragma once

#include <string>

struct Node
{
    size_t idx_node; // Own node index (ranging from 0 to n)
    size_t idx_way;
    
    unsigned long long idx_node_OSM; // Index as used in OSM
    
    double lon;
    double lat;
    
    int tile_x;
    int tile_y;
    
    std::string way_type;
    
    // Define constructors
    
    Node() = default;
    
    Node(size_t      const idx_node,
         size_t      const idx_way,
         unsigned long long const idx_node_OSM,
         double      const lon,
         double      const lat,
         int         const tile_x,
         int         const tile_y,
         std::string const way_type)
    :
      idx_node     (idx_node),
      idx_way      (idx_way),
      idx_node_OSM (idx_node_OSM),
      lon          (lon),
      lat          (lat),
      tile_x       (tile_x),
      tile_y       (tile_y),
      way_type     (way_type)
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