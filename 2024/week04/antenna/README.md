# Antenna

## Algorithmic Problem Description

Given a set of points $P$ in the $\mathbb{R}^2$ plane, find the minimum $d$ s.t. $\exists \ m \in \mathbb{R}^2 : \forall p \in P: ||m-p|| \leq d$.

## Solution Appraoch

This problem can be solved using the Min_circle_2 class from CGAL. 


## Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|-----------|---------|------------|---------|----------------|
| 1 | 10 pts | 1 s | Correct | 0.001s |
| 2 | 10 pts | 1 s | Correct | 0.003s |
| 3 | 20 pts | 1 s | Correct | 0.018s |
| 4 | 20 pts | 1 s | Correct | 0.276s |
| 5 | 10 pts | 1 s | Correct | 0.577s |
| 6 | 10 pts | 1 s | Correct | 0.000s |
| 7 | 10 pts | 1 s | Correct | 0.402s |
| 8 | 10 pts | 1 s | Correct | 0.402s |
| **Total** | **100/100** | - | - | - |