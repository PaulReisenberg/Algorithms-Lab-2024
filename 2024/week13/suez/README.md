# Suez

## Solution Concept

This problem can be solved using linear programming. The variables are the scaling factors $a_0, .., a_{n-1}$. We must encode two types of constraints:

- new posters may not intersect with other posters. This constraint ist inistantiated with evey pair of posters and must only be done for one dimension (x or y)

- new posters my not intersect with old ones. For each new poster we only need to find the one poster that it would hit first and encode this condition


## Learnings
- Use DBL_MAX for the max value
- use CGAL::Gmpq for exact fractions


## Test Results

Here's a formatted table for your README using markdown:

| Test Set | Points | Time Limit | Result | Actual Time |
|----------|---------|------------|---------|-------------|
| 1 | 25 pts | 1.500 s | ✓ Correct | 0.138 s |
| 2 | 25 pts | 1.500 s | ✓ Correct | 0.404 s |
| 3 | 25 pts | 1.500 s | ✓ Correct | 0.686 s |
| 4 | 25 pts | 1.500 s | ✓ Correct | 0.762 s |

