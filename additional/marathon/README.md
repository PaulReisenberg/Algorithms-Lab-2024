# Marathon

## Algorithmic Problem Description

The Algoland Marathon problem involves computing the maximum number of runners that can participate in a race given a graph $G=(V,E)$ with $|V| \leq 10^3$ vertices (intersections) and $|V| \leq 5 \cdot 10^3$ edges (streets). Each edge $e \in E$ has two attributes: width $w_e$ (number of runners that can fit side by side) and length $l_e$. Given start vertex $s$ and finish vertex $f$, runners must follow shortest paths from $s$ to $f$, but can choose different paths. All runners start simultaneously and run at the same speed, meaning runners taking the same street must fit side by side within that street's width. The challenge is to find the maximum number of runners that can be accommodated when they optimally coordinate their path choices.

## Solution Approach

We can solve this problem using Max Flow Min Cost combined with Binary Search. See main.cpp


