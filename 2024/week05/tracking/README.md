# Tracking 

## Problem Description

We are given a weighted undirected graph $G$. Some of the edges in $E$ are special. Given a start $u$ and finish node $v$, we must find the shortes path from $u$ to $v$ under the constraint that we use at least $k$ special edges.

## Solution Appraoch

We can solve this problem using Dijkstra and an augmented graph $G'$. To construct $G'$, we dublicate the original graph $k+1$ times. Such that we have nodes ${(l,i)}$ with $l < k$ and $\{{(l,i)}, {(l,j)}\} \in E' \Leftrightarrow \{i,j\} \in E$. Additionally we add $\{(l,i), (l+1,j)\}$ if $\{i, j\}$ is special. Now we only need to use Dijkstra to find the shortest path from $\{0,u\}$ to $\{k,v\}$.


## Test Results

| Test Set | Points | Time Limit | Result | Actual Time |
|----------|---------|------------|---------|-------------|
| 1 | 15 pts | 0.600 s | Correct answer | 0.002s |
| Hidden 1 | 05 pts | 0.600 s | Correct answer | 0.002s |
| 2 | 15 pts | 0.600 s | Correct answer | 0.023s |
| Hidden 2 | 05 pts | 0.600 s | Correct answer | 0.023s |
| 3 | 25 pts | 1.800 s | Correct answer | 0.547s |
| Hidden 3 | 05 pts | 1.800 s | Correct answer | 0.547s |
| 4 | 25 pts | 1.600 s | Correct answer | 0.553s |
| Hidden 4 | 05 pts | 1.600 s | Correct answer | 0.553s |

Total Score: 100