# Boats

## Algorithmic Problem Description

We are given two arrays of length $n$ where $p_i$ denotes the position of the ring for the $i$th boat and $l_i$ denotes the length of the $i$th boat. We must find the maximum number of boats that can be parked at the dock such that no boats overlap and each ring is contained within its assigned boat.

## Solution Approach

Since each ring is assigned to a unique boat, we can solve this using dynamic programming. We define $dp[i][val]$ as the maximum number of boats that can be parked considering only the first $i$ boats, and $dp[i][pos]$ as the rightmost occupied position to achieve this value. The $dp$ transitions are:

$$
\begin{aligned}
& \text{if } dp[i-1][pos] < p_i: \\
& \quad dp[i][val] = dp[i-1][val] + 1 \\
& \quad dp[i][pos] = \max(dp[i-1][pos], p_i) + l_i \\
& \text{else:} \\
& \quad dp[i][val] = dp[i-1][val] \\
& \quad \text{if } dp[i-2][pos] < p_i: \\
& \quad \quad dp[i][pos] = \min(dp[i-1][pos], \max(dp[i-2][pos], p_i) + l_i) \\
& \quad \text{else:} \\
& \quad \quad dp[i][pos] = dp[i-1][pos]
\end{aligned}
$$









## Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|--------|------------|--------|----------------|
| 1        | 30 pts | 2 s        | Correct answer | 0.004s |
| 2        | 30 pts | 2 s        | Correct answer | 0.009s |
| 3        | 40 pts | 2 s        | Correct answer | 1.019s |
