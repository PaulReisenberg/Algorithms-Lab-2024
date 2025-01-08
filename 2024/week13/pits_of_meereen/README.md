# Fighting Pits of Meereen

## Algorithmic Problem Description

Given a queue of $n$ fighters, each with a type in $[0,k-1]$, assign them sequentially to North or South entrance. When placing a fighter at an entrance in round $i$, that round's excitement is: $1000$ times the number of distinct types among the last $m$ fighters at that entrance, minus $2^{|p-q|}$ where $p,q$ count total fighters sent to each entrance through round $i$. The task is to maximize total excitement across all rounds while keeping each round's excitement non-negative. Each entrance tracks at most $m$ previous fighters, or fewer if less visited. Constraints: $1 \leq n \leq 5000$ fighters, $2 \leq k \leq 4$ types, $2 \leq m \leq 3$ memory length.

## Solution Appraoch

The first thing we notice are the unusually low bounds for $k$ and $m$. This means we can probably precompute the value for all alternatives leading us to a dynamic programming appraoch.

What information do we need to decide where to send the $i$-th fighter?

1. What are the last $m-1$ fighters that went to the north and south enterence before fighter $i$

2. what is the current value of p - q. The maximum value we need to consider is $+/-11$ because if $|p-q| > 11$ the score is negative for sure.

3. How much total excitement can we generate after we sent the $i$-th fighter to the north and south enterence

So we have to store a table of maximum size:

- $5000$ : maximum number of fighters in the queue
- $\times 5 \times 5$ : Maximum number possible combinations of fighters that went before us to the north gate 
- $\times 5 \times 5$ : Maximum number possible combinations of fighters that went before us to the south gate 
- $\times 23$: Possible values of $p-q$

    $= 71.875.000$ (large, but feasible)

Using this appraoch we pass 3/4 tests.

### Pruning Impossible States

To pass the last test, we need to optimize the code by pruning impossible states:

1. For each fighter, we only need to consider half of the possible values of p-q, as we can only change the value by $+1$ and $-1$ each iteration.

2. We use the $k+1$-th fighter type to signal that the current fighter has no predecessor or pre-predecessor. It is impossible to have a pre-predecessor but no predecessor, so we can prune those combinations.

3. Skip states where neither entrance's last fighter matches the current fighter's predecessor. We apply the same rule for the pre-predecessor.


## Test Results

| Test Set | Points | Time Limit | Result | Runtime |
|----------|---------|------------|---------|----------|
| 1 | 25 pts | 2 s |  Correct | 0.130s |
| 2 | 25 pts | 2 s |  Correct | 0.446s |
| 3 | 25 pts | 2 s |  Correct | 0.443s |
| 4 | 25 pts | 2 s |  Correct | 1.727s |

**Total Score: 100/100**

What even are the fighting pits of Meereen? [Here](https://www.youtube.com/watch?v=GlXv66gFtbI&ab_channel=FirstofHisName) is a video.