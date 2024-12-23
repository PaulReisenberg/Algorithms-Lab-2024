# Ceryneian Hind

## Algorithmic Problem Description

We are given a directed Graph $G = (V,E)$. We must find a subset $S \subseteq V$ of vertices such that $\nexists (u,v) \in E$ with $u \in S$ and $v \notin S$. Furthermore, each vertex is associated with a score $s_v$ and we must find the subset $S$ that maximizes the sum of scores in $S$. The sum of scores must be positive, otherwise the problem can't be solved.

## Solution Approach

The difficulty of this problem (at least for me) was to figure out that this problem can be solved using Max Flow. Once you realize this, it becomes quite easy. The idea works as follows: We set the capacity of each edge in the Graph to $\infty$. We then connect each vertex with a positive score to the source and each vertex with a negative score to the sink with the capacity being the absolute score of that vertex. Now if there is a semi dead-end $S$ with a positive sum of scores, that means that more is flowing in than can flow out. If there is a second one with a positive score, we can simply combine the two sets and end up with a "better" one. Luckily, we are not interested in the vertices that belong to $S$; we are only interested in the score, which is just the difference between the capacity from the source and the total flow. It is also convenient that the score must be positive so that we can simply ignore cases where the best score would be negative, which we would not be able to detect with this method, as the capacity from the source would always equal the total flow.

## Learnings
- Input size usually hints at solution appraoch

## Test Results


| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| Test set 1 | 25 pts | 0.500 s | Correct answer | 0.016s |
| Test set 2 | 25 pts | 0.500 s | Correct answer | 0.024s |
| Test set 3 | 15 pts | 0.500 s | Correct answer | 0.019s |
| Test set 4 | 15 pts | 1.000 s | Correct answer | 0.045s |
| Hidden test set 1 | 5 pts | 0.500 s | Correct answer | 0.016s |
| Hidden test set 2 | 5 pts | 0.500 s | Correct answer | 0.020s |
| Hidden test set 3 | 5 pts | 0.500 s | Correct answer | 0.018s |
| Hidden test set 4 | 5 pts | 1.000 s | Correct answer | 0.047s |

**Total Score: 100**



