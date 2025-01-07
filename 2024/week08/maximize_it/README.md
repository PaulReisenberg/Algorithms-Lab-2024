# Maximize It!
## Problem Description
We encounter two types of optimization problems involving linear programming:

1. Maximization problem:
   ```
   max b·y - a·x 
   s.t. x, y ≥ 0
        x + y ≤ 4
        4x + 2y ≤ ab
        -x + y ≤ 1
   ```

2. Minimization problem:
   ```
   min a·x + b·y + z
   s.t. x, y, z ≤ 0
        x + y ≥ -4
        4x + 2y + z ≥ -ab
        -x + y ≥ -1
   ```

Given parameters a and b, determine the optimal value for each type of problem.

## Solution Approach
We solve this using CGAL's Linear Programming solver. For each problem type:
1. Set up the constraints and objective function
2. Handle the three possible outcomes:
   - Unbounded solution
   - No feasible solution
   - Optimal solution exists (rounded according to problem type)

For maximization problems, we round down to the next integer, and for minimization problems, we round up.

## Test Results
| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| 1 | 50 pts | 0.100 s | Correct | 0.000s |
| 2 | 50 pts | 0.100 s | Correct | 0.000s |
| **Total** | **100/100** | - | - | - |