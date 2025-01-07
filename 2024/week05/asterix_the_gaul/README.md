# Asterix the Gaul

## Algorithmic Problem Description
We are given $n$ tuples $(d_j, t_j)$. Furthermore, we are given $m+1$ values $s_0$, ..., $s_m$ ($s_0 = 0$) and two values $D$ and $T$. We have to select a subset of tuples $S$ according to:

min $i$


s.t.


$\Sigma_{(d,t) \in S} \ d \geq D - s_i \cdot |S|$


$\Sigma_{(d,t) \in S} \ t < T$

## Solution Approach
The problem is obviously $NP$-complete. The first question I asked myself was if the subproblems for a fixed value of $i$ could be reduced to one another. This, however, does not seem possible, as an increased $i$ leads to an increase for every movement Asterix makes. This in essence creates a completely new set of tuples where each $d$ is increased by $s_i$. Therefore, the best solution I can think of is a binary search using split and list, leading to a time complexity of $\mathcal{O}(n \ log \ n \cdot 2^{n/2})$.

## Implementation
My implementation consists of creating two lists $l1$ and $l2$ for the split and list algorithm. In each list, I store tuples $(t, d, s)$ representing:
- $t$: the sum of time needed for the movements
- $d$: the total distance covered by the movements
- $s$: the number of movements used

I then do a binary search on the number of potions that Asterix needs to take. In each iteration, we check if it is possible to reach his friend by:
1. Removing all suboptimal movement combinations
2. Iterating through $l1$ and doing a binary search on $l2$

## Test Results
| Test Set | Points | Time Limit | Result | Actual Time |
|-----------|---------|------------|---------|-------------|
| 1 | 20 pts | 5 s | ✓ | 0.004s |
| 2 | 20 pts | 5 s | ✓ | 0.005s |
| 3 | 20 pts | 5 s | ✓ | 0.418s |
| 4 | 40 pts | 5 s | ✓ | 0.697s |

**Total Score: 100 points**