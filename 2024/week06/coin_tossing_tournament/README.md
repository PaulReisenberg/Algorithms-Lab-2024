# Coin Tossing Tournament
## Problem Description
In a tournament between $n$ players, $m$ rounds of coin tosses determine who has to do the homework. In each round, two predetermined players face each other, with the winner receiving one point and the loser zero points. While some round results were recorded, others were missed in the excitement. Given a final scoreboard from your friends showing you lost, you need to determine if this scoreboard could be legitimate given the known results and schedule.

## Solution Approach
This problem can be modeled as a Max Flow problem. Each of the $m$ games awards one point to the winner. The games with unrecorded winners should be able to fill the gaps between our recorded scoreboard and the final scoreboard provided by our friends.

We create a source and connect it to each node representing a game with an unrecorded outcome. The capacity of this edge is $1$. Each game node is then connected to nodes representing the players in that game. Each player node is then connected to the sink with a capacity equal to the difference between our score and the score our friends claimed. If this difference is ever negative or the sum of unrecorded games is unequal to the points missing in our score, we know they are lying.

We then only need to check if the max flow equals the number of missing games. If so, our friends might be telling the truth.

## Test Results
| Test Set | Points | Time Limit | Result | Execution Time |
|-----------|---------|------------|---------|----------------|
| 1 | 40 pts | 1 s | Correct | 0.007s |
| 2 | 40 pts | 1 s | Correct | 0.090s |
| 3 | 20 pts | 1 s | Correct | 0.241s |
| **Total** | **100/100** | - | - | - |