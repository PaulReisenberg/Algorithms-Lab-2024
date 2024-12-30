Here's the text with grammar corrections:

# Sith
## Problem Description
We are given a list of $n$ points $p_0, ..., p_{n-1}$ in the $\mathbb{R}^2$ plane and a value $r$. We must find the largest $k$ such that we can pick $r_0, ..., r_{k-1} \in \{p_k, ..., p_{n-1}\}$ such that for every $j \in \{1,...,k-1\}$ there exists $i \in \{0,...,j-1\}$ with $||r_j - r_i|| \leq r$

## Solution Approach
We can solve this problem by using Binary Search and the Delaunay Triangulation. We only need to search the interval $1$ to $k/2$, and for each $k$ we can check if it fulfills our conditions by:
1. Creating the Delaunay Triangulation on $\{p_k, ..., p_{n-1}\}$
2. Finding the largest connected component in the Delaunay Triangulation (distance $< r$)
3. If the component size is $\geq k$ then it is valid

Why does this work? We know that the Delaunay Triangulation contains the MST. Let's assume that $||r_j - r_i|| \leq r$ but the edge is not part of the Triangulation and there is no path between $r_j$ and $r_i$ of edges $\leq r$ in our Triangulation. Because we know that the Delaunay Triangulation contains the MST, we could look at the connected component in the MST $comp(r_i)$ and $comp(r_j)$. We know that these two components are connected by a path where one edge is $\geq r$ (our assumption). We could remove this edge and add the edge $(r_i, r_j)$ to the MST and get a better Spanning Tree, which is a contradiction. Thus, $(r_i, r_j)$ must be part of the Delaunay Triangulation if there is no other path of edges $\leq r$ that connects the two nodes.

## Test Results

| Test Set | Points | Time Limit | Result | Actual Time |
|----------|---------|------------|---------|-------------|
| 1 | 25 pts | 2 s | Correct answer | 0.048s |
| 2 | 25 pts | 2 s | Correct answer | 0.152s |
| 3 | 25 pts | 2 s | Correct answer | 0.473s |
| 4 | 25 pts | 2 s | Correct answer | 1.175s |

Total Score: 100