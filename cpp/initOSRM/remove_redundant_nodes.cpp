//
//  remove_redundant_nodes.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 18/03/2023.
//
// Removes nodes with a traveling distances smaller than a given threshold.
// Sometimes there is a node for left and right lane which is essentially
// the same coordinate.
//
// TODO the redundant nodes are not actually removed
// For now there seem to be so few redundant nodes that I skip this

#include "./initOSRM.ih"

void InitOSRM::remove_redundant_nodes(int const threshold)
{
    // TODO, the OSRM solver can be a class member
    
    osrm::EngineConfig config;

    config.storage_config = {"/Users/michiel/Dropbox/programming/OSM_data/Groningen/groningen-latest.osrm"};
    config.use_shared_memory = false;
    config.algorithm = osrm::EngineConfig::Algorithm::MLD;

    osrm::OSRM const osrm{config};
    
    size_t const nNodes = d_nodes.size();

    vector<size_t> redundant;
    redundant.reserve(500);

    #pragma omp parallel for
    for (size_t idx_node1 = 0; idx_node1 < nNodes; ++idx_node1)
    {
        Node const &node1 = d_nodes[idx_node1];

        for (size_t idx_node2 = idx_node1 + 1; idx_node2 < nNodes; ++idx_node2)
        {
            Node const &node2 = d_nodes[idx_node2];

            if (abs(node1.lat - node2.lat) > 0.005)
                continue;

            if (abs(node1.lon - node2.lon) > 0.005)
                continue;

            osrm::RouteParameters params;

            params.coordinates.push_back({util::FloatLongitude{node1.lon}, util::FloatLatitude{node1.lat}});
            params.coordinates.push_back({util::FloatLongitude{node2.lon}, util::FloatLatitude{node2.lat}});

            engine::api::ResultT result = json::Object();

            auto const status = osrm.Route(params, result);
            auto &json_result = result.get<json::Object>();

            if (status == Status::Ok)
            {
                auto &routes = json_result.values["routes"].get<json::Array>();

                // Let's just use the first route
                auto &route = routes.values[0].get<json::Object>();

                double const distance = route.values["distance"].get<json::Number>().value;

                if (distance <= threshold)
                {
                    #pragma omp critical
                    {
                        redundant.push_back(idx_node2);
                    }
                }
            }
        }
    }

    cout << "Nodes:     " << nNodes << endl;
    cout << "redundant: " << redundant.size() << endl;

    sort(begin(redundant), end(redundant));
    auto it = unique(begin(redundant), end(redundant));

    redundant.resize(distance(begin(redundant), it));

    cout << "redundant: " << redundant.size() << endl;
}
