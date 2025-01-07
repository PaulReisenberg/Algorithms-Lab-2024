# Diet
## Problem Description
We are given certain nutrients and requirements for how much we need of each nutrient. Additionally, we are given foods that each have a price and a certain amount of each nutrient. We must minimize the amount of money we spend on our diet while adhering to the nutrient specifications.

## Solution Approach
This problem can be solved using Linear Programming. Looking at the input size, we see that $m \leq 40$ and $n \leq 100$, which is within the range of input sizes that an LP can handle.

Formalizing the problem:
$$
\text{minimize} \ \sum_{i=0}^{m-1} \ p_i
$$
$$
\sum_{j=0}^{m} \ C_{j,i} \leq \text{max}_i \quad \forall i
$$
$$
\sum_{j=0}^{m} \ C_{j,i} \geq \text{min}_i \quad \forall i
$$

## Test Results
| Test Set | Points | Time Limit | Result | Execution Time |
|-----------|---------|------------|---------|----------------|
| 1 | 35 pts | 0.200 s | Correct | 0.001s |
| 2 | 35 pts | 0.200 s | Correct | 0.005s |
| 3 | 30 pts | 0.200 s | Correct | 0.070s |
| **Total** | **100/100** | - | - | - |