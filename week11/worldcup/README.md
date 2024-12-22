# Worldcup

## Solution

This problem can be solved by using linear programming. The constraints are easy to encode. The only difficulty is to figure out how many contour lines are between the warehouse and the stadium This can be done by first checking which contour lines are actually releveant using Dealunay Triangulation and then checking for each pair of warehouse and stadium how many lie between, which can be done naively by checking them all.

## Test Results


| Test set | Points | Time Limit | Result | Time |
|----------|---------|------------|---------|------|
| 1 | 25 pts | 4 s | ✓ | 0.094s |
| 2 | 25 pts | 4 s | ✓ | 0.241s |
| 3 | 25 pts | 4 s | ✓ | 0.256s |
| 4 | 25 pts | 4 s | ✓ | 1.512s |

## Learnings
- remember this: std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

- write the floor_to_long function correctly!