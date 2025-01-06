# The Great Game

## Problem Description

The Great Game is played on an n-position board with directed transitions from lower to higher numbered positions, ending at position n (target). Two meeples (red and black) are in play. Holmes moves first with red, then players alternate turns. On even-numbered turns, a player moves their original meeple (Holmes: red, Moriarty: black); on odd-numbered turns, they move the opposite meeple. A move consists of following one transition. The first player to get their meeple (Holmes: red, Moriarty: black) to the target wins. All positions can reach the target through transitions, and meeples can occupy the same position. Who has the winning strategy?

## Solution Appraoch

We can exploit the fact that there are only transitions from lower valued fields to higher valued fields using a dynamic programming appraoch. We could denote dp[r][b][even] as the result of the game if the red meeple is at the postion $r$, the black meeple at the position $b$ and it is Sherlock's (even) move. Similarly for uneven. However this is too slow ($\mathcal{O}(n^2)$).

A better appraoch would be to count the number of moves it takes to move a meeple from a position to the target position. dp[i][0] denotes the number of moves if the player belonging to this meeple is moving it from position $i$ (he wants to minimize the number of steps) and dp[i][1] if the oponent is moving it. This allows us to get to a runtime of $\mathcal{O}(n)$.

```text
dp[n][0] = 0
dp[n][1] = 0

for p = n-1 to 1:
    for (p, v) ∈ E:
        dp[p][0] = min(dp[p][0], 1 + dp[v][1])
        dp[p][1] = max(dp[p][1], 1 + dp[v][0])

Sherlock wins iff dp[r][0] ≤ dp[b][0]
```


### Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|--------|------------|--------|----------------|
| 1 | 25 pts | 3.500 s | Correct | 0.000 s |
| 2 | 25 pts | 3.500 s | Correct | 0.001 s |
| 3 | 25 pts | 3.500 s | Correct | 0.041 s |
| 4 | 25 pts | 3.500 s | Correct | 2.663 s |

