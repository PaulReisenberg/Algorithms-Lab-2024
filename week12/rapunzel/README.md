# Repunzel

## Algorithmic Problem Description

We are given a directed graph $G(V, E)$ with $n$ vertecies starting at vertex $0$. Each vertex has at most one edge pointing to it. 
Each vertex $v$ is associated with a value $b_v$. We must find all paths of length $m-1$ such that that the difference between the highest and the lowest value $b_v$ of the $m$ vertecies in this is not larger than $k$.

## Solution Appraoch

My solution currently only accieves 60%. If you know how to get to 100% let me know.

## Test Results



| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| 1 | 20 pts | 4 s | Correct | 0.013s |
| 2 | 20 pts | 4 s | Correct | 1.502s |
| 3 | 20 pts | 4 s | Correct | 0.004s |
| 4 | 40 pts | 4 s | Time limit exceeded | - |
| **Total** | **60/100** | - | - | - |



## Learnings

- If too slow check if you used references everywhere
- Go for the best solution first
- throw more space complexity at the problem if it is not fast enough


