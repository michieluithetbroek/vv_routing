//
//  node.h
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/03/2023.
//

#pragma once

#include <string>
#include <iomanip>

struct Node
{
    size_t idx_node; // Own node index (ranging from 0 to n)
    size_t idx_way;
    
    unsigned long long idx_node_OSM; // Index as used in OSM. TODO remove?
    
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
    
    // Nodes are sorted such that all nodes in a tile have consecutive indices.
    // For instance, node 1-8 can belong to tile 1 and node 9-15 to tile 2. Within
    // a tile, nodes are ordered from bottom to top and from left to right.
    
    bool operator<(Node const &node2) const
    {
      if (tile_y < node2.tile_y)
          return true;
   
      if (tile_y == node2.tile_y and tile_x < node2.tile_x)
          return true;
   
      if (tile_y == node2.tile_y and tile_x == node2.tile_x)
      {
          if (lat < node2.lat)
              return true;
          
          if (lat == node2.lat and lon < node2.lon)
              return true;
          
          return false;
      }

      return false;
    };
    
    
    bool operator==(Node const &other) const
    {
        return idx_node == other.idx_node;
    };
    
    friend std::ostream & operator<<(std::ostream &os, Node const &n)
    {
        os << std::fixed << std::setprecision(6)
           << std::setw(15) << n.idx_way      << ' '
           << std::setw(15) << n.idx_node_OSM << ' '
           << std::setw(10) << n.idx_node     << ' '
           << std::setw(15) << n.lon          << ' '
           << std::setw(15) << n.lat          << ' '
           << std::setw(10) << n.tile_x       << ' '
           << std::setw(10) << n.tile_y       << ' '
           << std::setw(20) << n.way_type     << '\n';
        
        return os;
    };
};
