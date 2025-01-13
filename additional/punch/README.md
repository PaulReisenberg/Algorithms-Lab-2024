# Punch

## Problem Description

Given $n$ beverages, each with a cost $c_i$ and volume $v_i$ in liters ($1 \leq c_i, v_i \leq 10^4$), and $k$ people ($1 \leq k \leq 10^4$), find the minimum total cost to create at least $k$ liters of punch using any combination of beverages (available in unlimited supply). If multiple combinations achieve the minimum cost, output both the minimum cost and the maximum number of distinct beverages possible among all minimum-cost combinations. For example, if both $\{2\times A, 2\times B\}$ and $\{4\times A\}$ achieve minimum cost for $k=4$, output minimum cost and 2 (not 1) as the maximum number of distinct beverages possible.

## Solution Approch

The important realization in my opionion here is that it suffices to only look at ordered sequences of beverages where $b_i \leq b_{i+1}$. If for example buying the beverages in sequence $4,2,3,3$ is  an optimal solution then $2,3, 3, 4$ is also an optimal solution. Building on the observation about ordered sequences, we can use a 2D dynamic programming approach where:
- The first dimension represents the required liters `i` (0 to k)
- The second dimension represents the highest beverage index `j` we can use (0 to n-1)
- Each cell stores both minimum cost and maximum distinct beverages possible

The DP state transition can be broken down into:

1. Base Cases (when required liters ≤ volume of current beverage):
```
if i ≤ liters[j]:
    if j == 0:
        dp[i][j] = (cost[j], 1)
    else:
        dp[i][j] = min((dp[i][j-1].cost, dp[i][j-1].beverages), 
                       (cost[j], 1))
```

2. Inductive Cases (when required liters > volume of current beverage):
```
if j == 0:
    dp[i][j] = (cost[j] + dp[i-liters[j]][j].cost, 1)
else:
    # Don't use beverage j
    dp[i][j] = dp[i][j-1]
    
    # Use beverage j once and then only beverages 0 to j-1
    cost_2 = dp[i-liters[j]][j-1].cost + cost[j]
    if cost_2 ≤ dp[i][j].cost:
        update dp[i][j] considering new distinct beverage
        
    # Use beverage j multiple times
    cost_3 = dp[i-liters[j]][j].cost + cost[j]
    if cost_3 ≤ dp[i][j].cost:
        update dp[i][j] maintaining same distinct count
```

The final answer is in `dp[k][n-1]`, giving both minimum cost and maximum distinct beverages possible. The solution runs in O(k*n) time and space.