
### Solution Concept

My solution uses dynamic programming to determine the optimal play for both players. Here's a brief explanation of the approach:

I use a 2D vector dp to store the minimum and maximum number of moves required to reach the target from each position.
The base case for the target position (n) is initialized with {0,0}.
Iterating backwards from n-1 to 1, I calculate for each position:

The minimum number of moves (best case for the current player)
The maximum number of moves (worst case for the current player)


These values are calculated based on the transitions available from each position and the previously calculated values for the destination positions.
After filling the dp table, I compare the minimum number of moves for the red and black meeples' starting positions to determine the winner:

If red can reach faster, Sherlock wins
If black can reach faster, Moriarty wins
If they can reach in the same number of moves, the winner depends on whether this number is odd or even


### Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|--------|------------|--------|----------------|
| 1 | 25 pts | 3.500 s | Correct | 0.000 s |
| 2 | 25 pts | 3.500 s | Correct | 0.001 s |
| 3 | 25 pts | 3.500 s | Correct | 0.041 s |
| 4 | 25 pts | 3.500 s | Correct | 2.663 s |

