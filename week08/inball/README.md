# Inball
## Problem Description
We are given a cave $C$ defined by a set of inequalities:
$C = \{x \in \mathbb{R}^n \mid a_i^Tx \leq b_i, i = 1, \ldots, n\}$
We must find the radius $r$ of the largest $d$-dimensional sphere that is contained in $C$. We are guaranteed that the norm of each point is an integer.

## Solution Approach
The problem can be solved by converting the formal problem description into a Linear Program. We introduce the variables $x = (x_0, ..., x_{d-1})^T$ representing the center of the sphere and the radius $r$. Now we must solve:
$\text{maximize} \ r$
subject to:
$a_i^Tx + ||a_i|| r \leq b_i \quad \forall i$

This can be derived by:
$a^T x \leq b$
$a^T(x+y) \leq b \quad ||y|| \leq r$
$a^Tx + a^Ty \leq b \quad ||y|| \leq r$
$a^Tx + a^T \frac{a}{||a||} r \leq b \quad ||y|| \leq r$
$a^Tx + ||a|| r \leq b \quad ||y|| \leq r$

## Test Results
| Test Set | Points | Time Limit | Result | Execution Time |
|-----------|---------|------------|---------|----------------|
| 1 | 35 pts | 2 s | Correct | 0.011s |
| 2 | 35 pts | 2 s | Correct | 0.101s |
| 3 | 30 pts | 2 s | Correct | 0.867s |
| **Total** | **100/100** | - | - | - |

