//
//  initOSM.h
//  vv_routing
//
//  Created by Michiel uit het Broek on 12/03/2023.
//
// This class handles reading OSM files and translates them into a vector of
// Nodes. Nodes have a unique index (ranging from 0 to n) and describe their
// coordinate and corresponding tile. Only nodes directly connected to a node
// in another tile are returned.
//
// Nodes can be printed to the terminal and are stored into a CSV file. This
// initial processing step is only required once and can be done for the
// entire Netherlands at once.

#pragma once

#include <vector>
#include <string>

#include "./../structs/node.h"

class InitOSM
{
    std::vector<Node> d_nodes;
    
public:
    
    InitOSM(std::string const fileName = "/Users/michiel/Dropbox/programming/OSM_data/Groningen/groningen-latest.osm.pbf");
    //InitOSM(std::string const fileName = "/Users/michiel/Dropbox/programming/OSM_data/netherlands-latest.osm.pbf");
    
    void print_nodes() const;
    void print_nodes_csv() const;
    
private:
    
    void nodes_make_unique();
    void nodes_reindex();
};
