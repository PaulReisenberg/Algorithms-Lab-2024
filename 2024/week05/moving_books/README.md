# Moving Books

## Problem Description

We are given $n$ friends with strength $s_i$ and $m$ boxes with weight $w_i$. We must find a mapping $S: [n] \mapsto [m]$ which minimizes
$t = max_{i \in [n]} | \{ j \in [m] | S(j) = i\} |$ under the constraint that $w_i \leq s_{S(i)} \ \forall i \in [m]$.

## Solution Appraoch

We can solve this problem with a greedy appraoch. We itereate through the friends and always assign the heaviest remaining box which this friend can carry. Doing this naively would yield a runtime of $\mathcal{O}(m^2)$, but we can do better. 

What if we first sort both the friends and weights in descending strength and weight? Well on average we should be faster but the worst case the sorting did not help and we are even worse of with $\mathcal{O}(mlog \ m + nlog \ n \ + \ m^2)$.

We can improve our appraoch by making the following observation: If a solution $t$ exists, then there exists a solution in which the strongest person carries the $t$ heaviest boxes then second strongest the next $t$ boxes and so on. Thus we only need to check if $weights[it] \leq strengths[i]$ until $it \geq m$. We can find the optimal $t$ with binary search leading to a worst case complextity of $\mathcal{O}(mlog \ m + nlog \ n + log(m)t)$.

## Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|--------|------------|--------|----------------|
| 1        | 20 pts | 1.500 s    | Correct answer | 0.004s |
| 2        | 40 pts | 1.500 s    | Correct answer | 0.243s |
| 3        | 40 pts | 1.500 s    | Correct answer | 0.439s |

