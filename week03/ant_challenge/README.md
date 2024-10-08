### Solution Concepts

For each species, I create a minimum spanning tree using Kruskal's algorithm. I then combine these trees by taking the minimum weight for each edge across all species' spanning trees.
Finally, I apply Dijkstra's algorithm on this combined graph to find the shortest path between the start and end nodes. This approach ensures that I'm using the fastest possible route, potentially switching between different species' networks as needed to minimize total travel time.

### Test Results


| Test Set | Points | Time Limit | Result         | Execution Time |
|----------|--------|------------|----------------|----------------|
| 1        | 20 pts | 1 s        | Correct answer | 0.01s          |
| 2        | 20 pts | 1 s        | Correct answer | 0.062s         |
| 3        | 20 pts | 1 s        | Correct answer | 0.062s         |
| 4        | 40 pts | 1 s        | Correct answer | 0.45s          |
