# Ant Challenge

## Problem Description

Given a graph with $n$ vertices, $e$ edges, and $s$ species, where each edge $(u,v)$ has a weight $w_i$ per species $i$. Each species has a home vertex and builds its private network using Dijkstra-like expansion (adding closest reachable vertex iteratively). Given start vertex $a$ and end vertex $b$, find shortest path from $a$ to $b$ where each edge must be in at least one species' network and can use minimum weight among available species. 

## Solution Appraoch

The networks of the ants are essentially a Minimum Spanning Tree (MST). From the problem statement, we know that this MST must be unique for each species, thus we can simply recreate it for each species using Kruskal's algorithm. I then combine these trees by taking the minimum weight for each edge across all species' spanning trees.
Finally, I apply Dijkstra's algorithm to this combined graph to find the shortest path between the start and end nodes. This approach ensures that I'm using the fastest possible route, potentially switching between different species' networks.


### Test Results


| Test Set | Points | Time Limit | Result         | Execution Time |
|----------|--------|------------|----------------|----------------|
| 1        | 20 pts | 1 s        | Correct answer | 0.01s          |
| 2        | 20 pts | 1 s        | Correct answer | 0.062s         |
| 3        | 20 pts | 1 s        | Correct answer | 0.062s         |
| 4        | 40 pts | 1 s        | Correct answer | 0.45s          |
