### Solution Concept

This problem becomes straightforward once you understand how to reduce the time complexity. The key insight is to first sort both the weights and the strengths. We know that a stronger person can carry all boxes that a less strong or equally strong person can carry. Therefore, to check if all the boxes can be carried to the van in t trips, we only need to verify if weights[i * t] <= strengths[i]. We then find the minimal t using binary search.

### Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|--------|------------|--------|----------------|
| 1        | 20 pts | 1.500 s    | Correct answer | 0.004s |
| 2        | 40 pts | 1.500 s    | Correct answer | 0.243s |
| 3        | 40 pts | 1.500 s    | Correct answer | 0.439s |

