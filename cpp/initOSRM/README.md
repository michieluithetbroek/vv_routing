This class transforms a list of [Nodes](https://github.com/michieluithetbroek/vv_routing/blob/master/cpp/structs/node.h) into a list of [Arcs](https://github.com/michieluithetbroek/vv_routing/blob/master/cpp/structs/arc.h) that describe the distance between two nodes.

First, a list of nodes is read from a given file as created by the class InitOSM. Then, for every pair of nodes that are at most `threshold` tiles away from each other, the traveling distance is computed using the Route option of OSRM. The direction is computed in both ways to allow for asymmetric routing problems. Note that OSRM returns the distance of the fastest path, not necessarily the shortest path. 

An Arc struct describes for a pair of nodes the from/to node indices, the x and y coordinate of the tile in which the from/to nodes are located, and the traveling distance and duration by bike.
