# James Bond's Sovereigns
## Algorithmic Problem Description
We are given a line of $n$ souvenirs with values $s_0, s_1, ..., s_{n-1}$ and $m$ passengers. The passengers take turns picking a souvenir from either end of the line. What is the maximum guaranteed value passenger $k$ (indexed at $0$) can attain?

## Solution Approach
This problem can be solved using dynamic programming. Each passenger has two choices when it is their turn: pick a souvenir from either the left or right end, which creates two different subproblems. Passenger $k$ wants to maximize their winnings (current pick + expected future winnings), while other passengers aim to minimize passenger $k$'s winnings in the resulting subproblem. It is $k$'s turn when $(n - \text{current number of souvenirs}) \text{ mod } m = k$.

We use a two-dimensional DP table where:
$$
dp[i][j] = \text{maximum guaranteed value for player k in the range }[i,j]
$$

Base case:
$$
dp[i][i] = \begin{cases}
s_i & \text{if } (n - i - 1) \text{ mod } m = k\\
0 & \text{otherwise}
\end{cases}
$$

Recurrence relation:
$$
dp[i][j]=
\begin{cases}
\max\{s_i + dp[i+1][j], s_j + dp[i][j-1]\} & \text{if } (n - (j-i+1)) \text{ mod } m = k\\
\min\{dp[i+1][j], dp[i][j-1]\} & \text{otherwise}
\end{cases}
$$

## Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|-----------|---------|------------|---------|----------------|
| 1 | 20 pts | 2 s | Correct | 0.118s |
| 2 | 40 pts | 2 s | Correct | 0.237s |
| 3 | 20 pts | 2 s | Correct | 0.359s |
| Hidden 1 | 5 pts | 2 s | Correct | 0.118s |
| Hidden 2 | 10 pts | 2 s | Correct | 0.237s |
| Hidden 3 | 5 pts | 2 s | Correct | 0.359s |
| **Total** | **100/100** | - | - | - |