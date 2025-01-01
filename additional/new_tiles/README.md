# New Tiles

## Problem Description
Given a rectangular grid where:
- '1' represents available cells
- '0' represents unavailable cells
Find the maximum number of 2x2 tiles that can be placed without overlapping.

## Solution Approach
Credits to [lizuoyue](https://github.com/lizuoyue) from whome I copied the solution. My contribution is simply this nice README that explains the approach.

The problem statement bounds $w$ to 17 which should already tell us that the solution is likely to be exponential in $w$. $2^{17}=131,072$ so it is fine to make a table of that size.

### 1. Input Processing
Instead of loading the data into a 2D vector, we store each row as a binary encoded int in a vector of length $h$.

Example:
```
Input row:    1 1 0 0 1
Stored as:    binary 11001 = decimal 25 in bitNum[i]

Code:
for (int j = 0; j < w; ++j) {
    num += bitMap[i][j] * (1 << (j));
}
```

### 2. State Preprocessing
We define a state as a binary number of length $w$. A one means this square can be covered by some 2x2 tile. For each state we calculate:

a) Number of consecutive vertical 1x2 tiles (twoOnes):
```
Row:      1 0 0 1 1 1
State:    1 1 0 0 1 1
Result:   1 vertical tile possible (at the end)
Code:
if ((i & (1 << j)) && (i & (1 << (j - 1)))) {
    twoOnes[i] += 1;
    j += 1;  // skip next bit to avoid overlap
}
```

b) Reachable states (lastState):
```
State:    1 1 1 0 1
Removes:  0 1 1 0 1  (removed first 1)
          1 0 1 0 1  (removed second 1)
          1 1 0 0 1  (removed third 1)
          1 1 1 0 0  (removed last 1)

Code:
lastState[i].push_back(i - (1 << j));
```

c) Vertical tile possibilities (numSquare):
```
Row i-1:  1 1 0 1 1
Row i:    1 1 1 0 1
State:    1 1 0 0 1
Result:   1 vertical 2x2 tile possible (at start)

Code:
numSquare[i][j] = twoOnes[(bitNum[i] & bitNum[i-1] & j)];
```

### 3. Dynamic Programming
The DP builds the solution row by row, starting from the second row. For each row i and state j:

1. First Phase - Horizontal Tiles:
```cpp
for (k = 0; k < lastState[j].size(); ++k) {
    dp[i][j] = max(dp[i][j], dp[i][lastState[j][k]]);
}
```
Try all states reachable by removing one tile placement position. This explores different ways to place horizontal 2x2 tiles in the current configuration.

2. Second Phase - Vertical Tiles:
```cpp
dp[i][j] = max(dp[i][j], dp[i-1][nS-1-j] + numSquare[i][j]);
```
Try placing vertical 2x2 tiles between rows i and i-1, then add the optimal solution for the remaining space in previous rows.

