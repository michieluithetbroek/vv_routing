//
//  initOSRM.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/03/2023.
//

#include "initOSRM.ih"

InitOSRM::InitOSRM()
{
    read_nodes_csv();
    
    osrm::EngineConfig config;

    config.storage_config = {"/Users/michiel/Dropbox/programming/OSM_data/Groningen/groningen-latest.osrm"};
    config.use_shared_memory = false;
    config.algorithm = osrm::EngineConfig::Algorithm::MLD;

    osrm::RouteParameters params;

    osrm::OSRM const osrm{config};
    
    auto const start = std::chrono::system_clock::now();
    
    params.coordinates.push_back({util::FloatLongitude{6.537585148221002}, util::FloatLatitude{53.23449806947688}});
    params.coordinates.push_back({util::FloatLongitude{6.538097594330374}, util::FloatLatitude{53.23343271364707}});
    
    engine::api::ResultT result = json::Object();
    
    auto const status = osrm.Route(params, result);
    
    auto &json_result = result.get<json::Object>();
    
    auto const end = std::chrono::system_clock::now();
    
    cout << "Time: " << (static_cast<double>((end - start).count())) / 1000000 << endl;
    
    if (status == Status::Ok)
    {
        auto &routes = json_result.values["routes"].get<json::Array>();

        // Let's just use the first route
        auto &route = routes.values[0].get<json::Object>();
        const auto distance = route.values["distance"].get<json::Number>().value;
        const auto duration = route.values["duration"].get<json::Number>().value;

        // Warn users if extract does not contain the default coordinates from above
        if (distance == 0 || duration == 0)
        {
            std::cout << "Note: distance or duration is zero. ";
            std::cout << "You are probably doing a query outside of the OSM extract.\n\n";
        }

        std::cout << "Distance: " << distance << " meter\n";
        std::cout << "Duration: " << duration << " seconds\n";
        
//        return EXIT_SUCCESS;
    }
    
    else if (status == Status::Error)
    {
        const auto code = json_result.values["code"].get<json::String>().value;
        const auto message = json_result.values["message"].get<json::String>().value;

        std::cout << "Code: " << code << "\n";
        std::cout << "Message: " << code << "\n";
        
//        return EXIT_FAILURE;
    }
}
