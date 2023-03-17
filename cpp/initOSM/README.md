This class defines the Node struct and handles reading an input OSM file. The result of this class is a single vector with Node objects. Each node object has the following members: way index, node index, own node index, latitude, longitude, tile index X, tile index Y, way type.

By default, the constructor reads all roads of the province Groningen (the Netherlands). First, we filter on highway type such that only roads that are suitable for bicycles remain. Then for all remaining roads, only nodes that are directly connected to a node in another tile are saved. 

The class is used as follows:

```
InitOSM initOSM;

initOSM.print_nodes();                 // Print nodes in terminal
initOSM.print_nodes_csv();             // Print nodes to CSV file

vector<Nodes> nodes(initOSM.d_nodes);  // Copy nodes to new vector
```

Sample terminal output:

<img width="676" alt="image" src="https://user-images.githubusercontent.com/9677284/224785201-fa14eb39-1275-4a0d-8c5b-98e0d14aa161.png">


Remark that we can also create a function that returns a r-value vector. Thereby we avoid that the user later on has to copy/move this vector.
