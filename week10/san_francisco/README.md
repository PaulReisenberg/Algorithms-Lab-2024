# San Francisco

## Problem Description

Given a directed weighted graph $G=(V,E)$ with $|V|=n$ nodes and $|E|=m$ edges, where node $0$ is the start and sinks can return to start for free. Each edge $(u,v,s) \in E$ goes from $u$ to $v$ and has a score $s$. A path consists of moves along edges accumulating scores, with optional free returns to start. Given target score $x$ and move limit $k$, find minimum moves needed for score $\geq x$, or report "Impossible". 

## Solution Appraoch

Solution uses dynamic programming with state $dp[i][j]$ denoting maximum score achievable in exactly $i$ moves starting from node $j$. The recurrence is:

```
for i=1 to k+1:
    for j=0 to n-1:
        dp[i][j] = max(dp[i-1][v] + s) for (u,v,s) in E
```

## Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| 1 | 30 pts | 4 s | Correct answer | 0.003s |
| 2 | 30 pts | 4 s | Correct answer | 0.045s |
| 3 | 40 pts | 4 s | Correct answer | 0.53s |