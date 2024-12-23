# Bistro

## Algorithmic Problem Description
We are given a sets of points $P$ and $L$. For each $p \in P$ we must output the squared eucledian distance to the closest point in $L$.

## Solution Approach
The naive appraoch would be to calculate the distance of each point in $P$ to every Point in $P$. This would take $\mathcal{O}(n \cdot m)$ time. Using Delaunay we can be faster. We can construct the Delaunay Triangulation in $\mathcal{O}(n \cdot \log(n))$ the nearest vertex can be found in $\mathcal{O}(\log(n))$ giving us a total runtime of $\mathcal{O}(n \log(n) + m \log(n))$. Much better ...

## Test Results
| Test set | Points | Time Limit | Result | Time |
|----------|---------|------------|---------|------|
| 1 | 20 | 0.600s | Correct answer | 0.026s |
| 2 | 20 | 0.600s | Correct answer | 0.162s |
| 3 | 20 | 0.600s | Correct answer | 0.140s |
| 4 | 20 | 0.600s | Correct answer | 0.212s |
| 5 | 20 | 0.600s | Correct answer | 0.460s |

Total score: 100