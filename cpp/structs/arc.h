//
//  arc.h
//  vv_routing
//
//  Created by Michiel uit het Broek on 18/03/2023.
//
// Arc that describes the distance between two nodes. This arc is
// computed using the shorest path function of OSRM. Distances are
// stored with arcs because an entire distance matrix would be much
// too expensive to compute.

#pragma once

struct Arc
{
    size_t idx_from;
    size_t idx_to;
    
    int tile_x_from;
    int tile_y_from;
    int tile_x_to;
    int tile_y_to;
    
    double distance;
    double time;
    
    Arc(size_t const idx_from,    size_t const idx_to,
        int const tile_x_from,    int const tile_y_from,
        int const tile_x_to,      int const tile_y_to,
        double const distance,    double const time)
    :
      idx_from    (idx_from),
      idx_to      (idx_to),
      tile_x_from (tile_x_from),
      tile_y_from (tile_y_from),
      tile_x_to   (tile_x_to),
      tile_y_to   (tile_y_to),
      distance    (distance),
      time        (time)
    { };
};
