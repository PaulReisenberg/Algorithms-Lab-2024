# Pied Piper
## Problem Description
The Pied Piper has to navigate through a city with n public squares numbered from 0 to n-1, connected by m one-way streets. Starting from square 0, he must find a path that ends back at square 0 and passes through square n-1. Each street contains a certain number of rats. The piper can't visit any square more than once (except square 0), and his path must be divided into exactly two parts: first moving through increasing square numbers until reaching n-1, then moving through decreasing square numbers back to 0. The goal is to maximize the total number of rats collected along this path.

## Solution Approach
To solve this problem, consider that we can split it into two paths: increasing and decreasing. By flipping the direction of all edges in the decreasing path, we can think of planning two simultaneous increasing paths from 0 to n-1.

Let dp[i][j] represent the maximum rats we can collect when one path reaches i and the other reaches j. We know dp[0][0] = 0 (starting point) and we want dp[n-1][n-1] (ending point). Since squares can't be visited twice (except 0), we avoid states where i = j.

For any state dp[i][j], we must have computed all states where the sum of positions is less than i+j. This is because each step moves either i or j forward by using one edge. Therefore, we can build our solution by iterating through increasing sums of positions.

## Test Results



| Test Case          | Points | Time Limit | Result          | Execution Time |
|-------------------|--------|------------|-----------------|----------------|
| Test set 1        | 25 pts | 4 s       | Correct answer  | 0.046s        |
| Test set 2        | 25 pts | 4 s       | Correct answer  | 0.046s        |
| Test set 3        | 15 pts | 4 s       | Correct answer  | 0.783s        |
| Test set 4        | 15 pts | 4 s       | Correct answer  | 1.117s        |
| Hidden test set 1 | 5 pts  | 4 s       | Correct answer  | 0.044s        |
| Hidden test set 2 | 5 pts  | 4 s       | Correct answer  | 0.047s        |
| Hidden test set 3 | 5 pts  | 4 s       | Correct answer  | 0.779s        |
| Hidden test set 4 | 5 pts  | 4 s       | Correct answer  | 1.105s        |

Total score: 100

