//
//  initOSRM.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/03/2023.
//
// TODO
// - Can the OSRM solver be a class member?

#include "initOSRM.ih"

// Entry of the directed distance matrix





InitOSRM::InitOSRM()
{
    int const radius = 4;
    
    read_nodes_csv();
    
    vector<Arc> entries;
    
    entries.reserve(2000000);
    
    // Create OSRM object
    osrm::EngineConfig config;

    config.storage_config = {"/Users/michiel/Dropbox/programming/OSM_data/Groningen/groningen-latest.osrm"};
    config.use_shared_memory = false;
    config.algorithm = osrm::EngineConfig::Algorithm::MLD;

    osrm::OSRM const osrm{config};
    
    
    // Compute distances
    
    // radius 0:  14 seconds, 15.361 nodes, 183 redundant, 363.609 arcs (XX),
    // radius 1: 143 seconds, 15.361 nodes, 2.730.000 arcs
    // radius 2: 643 seconds, 15.361 nodes2, 6.439.572 arcs
    // radius 4:
    
           
    auto const start = std::chrono::system_clock::now();
    
    size_t const nNodes = d_nodes.size();
    
    int cnt = 0;
    
    //#pragma omp parallel for
    
    for (size_t idx_node1 = 0; idx_node1 < nNodes; ++idx_node1)
    {
        Node const &node1 = d_nodes[idx_node1];
        
        for (size_t idx_node2 = 0; idx_node2 < nNodes; ++idx_node2)
        {
            Node const &node2 = d_nodes[idx_node2];
            
            if (node1.idx_node == node2.idx_node)
                continue;
            
            if (abs(node1.tile_y - node2.tile_y) > radius or abs(node1.tile_x - node2.tile_x) > radius)
                continue;
            
            ++cnt;
            
            if (cnt % 10000 == 0)
                cout << "-------" << cnt << "\n\n";
            
//            osrm::RouteParameters params;
//
//            params.coordinates.push_back({util::FloatLongitude{node1.lon}, util::FloatLatitude{node1.lat}});
//            params.coordinates.push_back({util::FloatLongitude{node2.lon}, util::FloatLatitude{node2.lat}});
//
//            engine::api::ResultT result = json::Object();
//
//            auto const status = osrm.Route(params, result);
//            auto &json_result = result.get<json::Object>();
//
//            if (status == Status::Ok)
//            {
//                auto &routes = json_result.values["routes"].get<json::Array>();
//
//                // Let's just use the first route
//                auto &route = routes.values[0].get<json::Object>();
//
//                double const distance = route.values["distance"].get<json::Number>().value;
//                double const duration = route.values["duration"].get<json::Number>().value;
//
//                #pragma omp critical
//                {
//                    entries.emplace_back(node1.idx_node, node2.idx_node,
//                                         node1.tile_x, node1.tile_y,
//                                         node2.tile_x, node2.tile_y,
//                                         distance, duration);
//                }
//
//                // Warn users if extract does not contain the default coordinates from above
////                if (distance == 0 || duration == 0)
////                {
////                    cout << node1.idx_node << " " << node1.lon << " " << node1.lat << endl
////                         << node2.idx_node << " " << node2.lon << " " << node2.lat << endl;
////
////                    std::cout << "Note: distance or duration is zero. ";
////                    std::cout << "You are probably doing a query outside of the OSM extract.\n\n";
////                }
//
////                std::cout << "Distance: " << distance << " meter\n";
////                std::cout << "Duration: " << duration << " seconds\n";
//
//                //        return EXIT_SUCCESS;
//            }
//
//            else if (status == Status::Error)
//            {
//                const auto code = json_result.values["code"].get<json::String>().value;
//                const auto message = json_result.values["message"].get<json::String>().value;
//
//                std::cout << "Code: " << code << "\n";
//                std::cout << "Message: " << code << "\n";
//
//                //        return EXIT_FAILURE;
//            }
        }
    }
    
    auto const end = std::chrono::system_clock::now();
    
    cout << "Time: " << (static_cast<double>((end - start).count())) / 1000000 << endl;
    
    cout << "arcs: " << cnt << endl;
    
    long int cnt2 = 0;
    long int cnt3 = 0;
    long int cnt4 = 0;
    long int cnt5 = 0;
    
    //    for (Entry const &entry: entries)
    //        if (entry.distance == 0)
    //        {
    //            cout << setw(10) << d_nodes[entry.idx_from].lon
    //                 << setw(10) << d_nodes[entry.idx_from].lat << endl
    //                 << setw(10) << d_nodes[entry.idx_to].lon
    //                 << setw(10) << d_nodes[entry.idx_to].lat << endl << endl;
    //        }
    
    for (Arc const &entry: entries)
        cnt2 += (entry.distance <= 0);
    
    for (Arc const &entry: entries)
        cnt3 += (entry.distance <= 1);
    
    for (Arc const &entry: entries)
        cnt4 += (entry.distance <= 5);
    
    for (Arc const &entry: entries)
        cnt5 += (entry.distance <= 10);
    
    cout << "counter = " << cnt2 << endl;
    cout << "counter = " << cnt3 << endl;
    cout << "counter = " << cnt4 << endl;
    cout << "counter = " << cnt5 << endl;
}
