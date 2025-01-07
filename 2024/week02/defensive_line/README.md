# Defensive Line

## Problem Description
We are given three integers $n$, $m$ and $k$. Additionally we are given $v_0,...,v_{n-1}$ 
Goal:

Maximize:

$\Sigma_{i=0}^{m-1} (b_i - a_i + 1)$

under the constraint:

$\Sigma_{j=a_i}^{b_i} v_j = k$


## Solution Approach

We can solve this problem using a dynamic programming approach. 

-  We use a sliding window approach to determine which segments of the defensive line we can cover with one attacking player. We sort these indices by the last value of each segment. We store the segments in a seq\_len, where seq\_len[$i$] = $x$ means that at defensive position $i$ a segment of size $x$ ends.

-  Now given our intervals for each attacking player, we need to cover the most amount of defensive players. We introduce two dimensions to solve this problem:
    
    1. $i$: total number of segments we can choose
    2. $j$: defensive index to which we take segments into account



$$
dp[i][j] = max(dp[i-1][j-seq\_len[j]] + seq\_len[j] \ , \ )
$$

## Test Results

| Test Set | Points | Time Limit | Status | Time |
|----------|---------|------------|---------|------|
| 1 | 20 pts | 0.500 s | Correct answer | 0.0s |
| 2 | 20 pts | 0.500 s | Correct answer | 0.005s |
| 3 | 20 pts | 0.500 s | Correct answer | 0.065s |
| 4 | 20 pts | 2.000 s | Correct answer | 0.006s |
| 5 | 20 pts | 0.500 s | Correct answer | 0.076s |

**Total Score:** 100 points