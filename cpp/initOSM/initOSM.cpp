//
//  initOSM.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 12/03/2023.
//

#include "initOSM.ih"

// Struct that implements a function way() which is called by the Osmium
// library. This function is applied to every way object in the OSM file
// that is read. In this function, we first filter on road type and then
// we only keep nodes for which a consecutive node lies in another tile.

struct OSM_handler: public osmium::handler::Handler
{
    unsigned long int d_nWays_processed  = 0;
    unsigned long int d_nNodes_processed = 0;
    
    std::vector<Node> d_nodes;
    
    // This function is called by Osmium for each way object
    
    void way(osmium::Way const &way)
    {
        ++d_nWays_processed;
        
        int constexpr zoom = 14;
        
        // Skip ways that are not valid anymore
        
        if (not way.visible())
            return;
        
        if (way.deleted())
            return;
        
        // Filter on highway types
        // Recall that in OSM every road is called a highway
        
        osmium::TagsFilter filter{false};
        
        filter.add_rule(true, "highway", "primary");
        filter.add_rule(true, "highway", "secondary");
        filter.add_rule(true, "highway", "tertiary");
        filter.add_rule(true, "highway", "unclassified");
        filter.add_rule(true, "highway", "service");
        
        filter.add_rule(true, "highway", "cycleway");
        
        filter.add_rule(true, "highway", "residential");
        filter.add_rule(true, "highway", "living_street");
        
        if (not osmium::tags::match_any_of(way.tags(), filter))
            return;
         
        // Process all nodes on this way
        // We only keep nodes for which a consecutive node lies in another tile
        
        osmium::NodeRefList const &nodes = way.nodes();
        
        size_t const nNodes = nodes.size();
        
        d_nNodes_processed += nNodes;
        
        for (size_t idx = 0; idx < nNodes; ++idx)
        {
            size_t const idx_prev = (idx > 0 ? idx - 1 : 0);
            size_t const idx_next = (idx < nNodes - 1 ? idx + 1 : nNodes - 1);
            
            // Get reference to node objects
            
            osmium::NodeRef const &node_prev = nodes[idx_prev];
            osmium::NodeRef const &node_curr = nodes[idx];
            osmium::NodeRef const &node_next = nodes[idx_next];
            
            // Get corresponding tile of each node
            
            osmium::geom::Tile const &tile_prev {uint32_t(zoom), node_prev.location()};
            osmium::geom::Tile const &tile_curr {uint32_t(zoom), node_curr.location()};
            osmium::geom::Tile const &tile_next {uint32_t(zoom), node_next.location()};
            
            // Save node if previous or next node lies in a different tile
            
            if (tile_curr.x != tile_prev.x or
                tile_curr.x != tile_next.x or
                tile_curr.y != tile_prev.y or
                tile_curr.y != tile_next.y)
            {
                d_nodes.emplace_back(node_curr.ref(),
                                     way.id(),
                                     node_curr.lon(),
                                     node_curr.lat(),
                                     tile_curr.x,
                                     tile_curr.y);
            }
        }
    }
};


InitOSM::InitOSM(string const fileName)
{
    cout << "Start processing OSM file" << endl << endl;
    
    using index_t = osmium::index::map::SparseMemArray<osmium::unsigned_object_id_type, osmium::Location>;
    using cache_t = osmium::handler::NodeLocationsForWays<index_t>;
    
    index_t index;
    cache_t cache{index};

    osmium::io::Reader reader{fileName,
        osmium::osm_entity_bits::node |
        osmium::osm_entity_bits::way};
    
    auto const start = std::chrono::system_clock::now();
    
    // Create a Osmium handler that processes all Way objects of the input_file (via reader)
    
    OSM_handler handler;
    osmium::apply(reader, cache, handler);

    // Move nodes from the Osmium handler into our own class member d_nodes
    
    d_nodes = std::move(handler.d_nodes);

    nodes_make_unique();
    nodes_reindex();

    auto const end = std::chrono::system_clock::now();
    
    cout << "nWays processed:     " << handler.d_nWays_processed  << '\n'
         << "nNodes processed:    " << handler.d_nNodes_processed << '\n'
         << "nNodes final:        " << d_nodes.size()             << '\n'
         << "Time: " << (static_cast<double>((end - start).count())) / 1000000 << endl;
}

