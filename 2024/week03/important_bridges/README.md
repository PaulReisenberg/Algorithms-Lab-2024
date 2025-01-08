# Important Bridges

## Problem Description

Given an undirected connected graph with $n$ nodes (islands) and $m$ edges (bridges). Find all bridges that, if removed, disconnect the graph into two components, and output them in lexicographically sorted order $(u,v)$ where $u < v$. 

## Solution Appraoch


The solution uses biconnected components - subgraphs that remain connected if any single vertex is removed. An edge is a bridge (critical) if it's the only edge in its biconnected component. We build the graph from input and use the boost biconnected_components algorithm to identify components. Edges in size-1 components are bridges. These are sorted lexicographically with smaller vertex first: $(u,v)$ where $u < v$.


### Test Scores

| Test Set   | Points | Time Limit | Result         | Execution Time |
|------------|--------|------------|----------------|----------------|
| Test set 1 | 40 pts | 2 s        | Correct answer | 0.005s         |
| Test set 2 | 40 pts | 2 s        | Correct answer | 0.384s         |
| Test set 3 | 20 pts | 2 s        | Correct answer | 0.000s         |