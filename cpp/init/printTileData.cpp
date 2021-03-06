//
//  printTileData.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::printTileData() const
{
    cout << "Tile sets:\n";
    
    for (int idx = 0; idx < d_nTileSets; ++idx)
    {
        auto const &tile = d_tileSets_perTile[idx];
        
        cout << setw(3) << idx << " - ";
        
        for (int v: tile)
            cout << v << ' ';
        
        cout << endl;
    }
    
    cout << "\nTile per node:\n";
    
    for (int idx_node = 0; idx_node < d_nNodes; ++idx_node)
        cout << setw(5) << idx_node << " " << setw(5) << d_tileSets_perNode[idx_node] << endl;
    
    cout << endl;
}
