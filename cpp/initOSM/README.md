This class defines the Node struct and handles reading an input OSM file. 

By default, the constructor reads all roads of the province Groningen (the Netherlands). First, we filter on highway type such that only roads that are suitable for bicycles remain. Then for all remaining roads, only nodes that are directly connected to a node in another tile are saved. 

The result of this class is a single vector with Node objects.
