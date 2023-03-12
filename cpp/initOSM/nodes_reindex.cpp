//
//  nodes_reindex.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 12/03/2023.
//
// Give nodes new indices from from 0 to n. These indices will be used
// throughout the project.

#include "initOSM.ih"

void InitOSM::nodes_reindex()
{
    for (size_t idx = 0; idx < size(d_nodes); ++idx)
        d_nodes[idx].idx_node = static_cast<int>(idx);
}
