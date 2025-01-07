# Casterly Rock

## Variable Definitions

Central to our constraints are the definitions of the two canals:

- sewage canal equation: $a_sx + b_sy = c_s$ because the sewage canal can't be horizontal, we set $b_s$ to 1. yielding: $x + b_sy = c_s$
- similarly for the water canal we get the equation $a_sx + y = c_w$



## Constraints



1. **Sewage Piple Separation Constraint**:
   
   For nobels:
   
   $x_i \leq c_s - b_sy
   \quad \Leftrightarrow  \quad 
   -c_s + b_sy_i \leq -x_i$

   For commons:

   $c_s - b_sy \leq x_i$

2. **Orthogonality Constraint**:
   
   $a_w + b_s = 0$
   
   Ensures the water and sewage canals meet at a right angle.

3. **Total Sewage Pipe Length Constraint** (if $s ≠ -1$):
   
   $\Sigma_{i \in houses} |x_i - (c_s - b_sy_i)| < s$ 
   
   ...
   
   $b_s(y_m - y_n) + c_s(m-n) ≤ s + x_n - x_m$
   
   Where:
   - $y_m, y_n$: sum of y-coordinates of commoner/noble houses
   - $x_m, x_n$: sum of x-coordinates of commoner/noble houses
   - $n, m$: number of noble/common houses
   
4. **Maximum Water Pipe Length** (if $s ≠ -1$):

   To keep track of the longest water pipe, we introduce a new variable $l_{max}$. This variable is constrained to be larger than ever water pipe by:
   
   $ y_i - (c_w - a_w x_i) \leq l_{max} \quad \quad \forall i$

   $ (c_w - a_w x_i) - y_i \leq l_{max} \quad \quad \forall i$

   Setting the objective function to min $l_{max}$ will yield the desired result.

## Learnings
- Look at the input type!!!!!!!!!!!! It took me 3 hours to find out it was int instead of long


## Test Results

| Test Set | Points | Time Limit | Result | Actual Time |
|----------|---------|------------|---------|-------------|
| 1 | 30 pts | 2 s | Correct answer | 0.162s |
| 2 | 30 pts | 2 s | Correct answer | 0.831s |
| 3 | 20 pts | 2 s | Correct answer | 0.448s |
| 4 | 20 pts | 2 s | Correct answer | 0.646s |
