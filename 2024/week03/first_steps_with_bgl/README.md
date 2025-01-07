### Solution Concept

In my solution, I approach this graph problem using two main algorithms: Kruskal's Minimum Spanning Tree and Dijkstra's Shortest Path. First, I use Boost's Graph Library to create a weighted undirected graph from the input. To find the total weight of the minimum spanning tree, I apply Kruskal's algorithm using boost::kruskal_minimum_spanning_tree. I then sum the weights of the edges in the resulting MST. For the second part of the problem, I use Dijkstra's algorithm (boost::dijkstra_shortest_paths) starting from node 0 to compute the shortest paths to all other nodes. I then find the maximum distance among these shortest paths, which gives the distance to the node furthest from 0. This approach efficiently solves both parts of the problem in a single pass through the graph, handling the given constraints on graph size and edge weights.



### Test Results

| Test Set      | Points | Time Limit | Result         | Execution Time |
|---------------|--------|------------|----------------|----------------|
| graphs_easy   | 30 pts | 1 s        | Correct answer | 0.000s         |
| graphs_medium | 70 pts | 1 s        | Correct answer | 0.045s         |