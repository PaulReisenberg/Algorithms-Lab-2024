### Problem Description

"The Great Game" is a board game played by Sherlock Holmes and Professor Moriarty. The game is played on a board with n positions (1 to n), where some positions are connected by transitions. Two meeples (red and black) start at given positions. Players alternate moving a meeple along one transition, with specific rules for which meeple to move based on the number of turns played. The game ends when a meeple reaches the target position (n), determining the winner. The task is to determine who has a winning strategy given the board layout and starting positions.


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

### Running Time
Test set 1 (25 pts / 3.500 s) : Correct answer      (0.0s)
Test set 2 (25 pts / 3.500 s) : Correct answer      (0.001s)
Test set 3 (25 pts / 3.500 s) : Correct answer      (0.041s)
Test set 4 (25 pts / 3.500 s) : Correct answer      (2.663s)

