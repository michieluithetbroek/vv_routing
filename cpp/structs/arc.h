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
//
// TODO Should this struct also handle reading a file of Arcs? Maybe
// we can create a struct Arcs that is a vector<Arc> which only adds
// the functionallity of reading/printing the data from/to a file

#pragma once

#include <ostream>
#include <iomanip>

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
    
    bool operator<(Arc const &arc2) const
    {
      if (idx_from < arc2.idx_from)
          return true;
   
      if (idx_from == arc2.idx_from and idx_to < arc2.idx_to)
          return true;

      return false;
    };
    
    friend std::ostream & operator<<(std::ostream &os, Arc const &arc)
    {
        os << std::fixed << std::setprecision(1)
        
           << std::setw(10) << arc.idx_from    << ' '
           << std::setw(10) << arc.idx_to      << ' '
           << std::setw(6)  << arc.tile_x_from << ' '
           << std::setw(6)  << arc.tile_y_from << ' '
           << std::setw(6)  << arc.tile_x_to   << ' '
           << std::setw(6)  << arc.tile_y_to   << ' '
           << std::setw(10) << arc.distance    << ' '
           << std::setw(10) << arc.time        << '\n';
        
        return os;
    };
};
