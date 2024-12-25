





# Alastor "Mad-Eye" Moody


## Algorithmic Problem Description

We are given a network with $n$ nodes and $m$ undirected edges, a start node $s$ and end node $p$. Each edge in the network has a capacity $c$ and a length $d$. It is guaranteed that there exists a path from $s$ to $p$ with positive capacity. 

Given the shortes path from $s$ to $p$ is $d_{opt}$ long, find the number simoultaneous possible paths from $s$ to $p$ of length $d_{opt}$ in the network.


## Solution Approach


1. Find shortest path in network
2. Use binary search in combination with max flow min cost to find the number of possible paths of that length


## My Mistakes

Again, this problem took me longer than it should have because of two mistakes I made: 

1. I did not read the description properly and missed, that the flyways can be used in both directions
2. I assumed int to be large enough to store the flow cost but it isn't.


## Results

Here's the test results formatted as a table in Markdown:

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| 1 | 25 pts | 1 s | Correct answer | 0.311s |
| 2 | 25 pts | 1 s | Correct answer | 0.144s |
| 3 | 25 pts | 1 s | Correct answer | 0.066s |
| 4 | 25 pts | 1 s | Correct answer | 0.260s |

**Total Score: 100**