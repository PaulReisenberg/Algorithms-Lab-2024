# Attack on King's Landing

## Problem Description

Given a graph $G=(V,E)$ with $n$ vertices and $m$ edges, $b$ barracks, and $p$ plazas, where each edge $e \in E$ has length $|e|$. A vertex $v$ is reachable from barracks $b$ if there exists a path $P=(v_0,\ldots,v_k)$ with $v_0=b$, $v_k=v$ and $\sum_{i=0}^{k-1}|e_i| \leq d$ where $e_i$ is the edge between $v_i$ and $v_{i+1}$. To make an edge safe, both endpoints must be barricaded. Regular vertices can barricade at most 1 incident edge, plazas can barricade 2 edges, and no edge connects two plazas. Each barracks can send unlimited troops to reachable vertices within distance $d$. The goal is to maximize the number of safe edges.

## Solution Appraoch

The solution consists of two parts:

1. Identify sealable intersections using BFS from each barracks, exploring until distance $d$ is exceeded. This gives the set of vertices where barricades can be built.

2. Apply Edmonds' Maximum Cardinality Matching algorithm to maximize sealed streets. Since plazas can seal two streets and no two plazas are adjacent, we duplicate plaza vertices and connect them to reachable regular intersections before running Edmonds' algorithm.


### Test Results

| Test Set | Points | Time Limit | Result | Runtime |
|-------------------|--------|------------|----------------|---------|
| Test set 1 | 15 pts | 1 s | Correct answer | 0.171s |
| Hidden test set 1 | 05 pts | 1 s | Correct answer | 0.177s |
| Test set 2 | 25 pts | 1 s | Correct answer | 0.082s |
| Hidden test set 2 | 05 pts | 1 s | Correct answer | 0.08s |
| Test set 3 | 15 pts | 1 s | Correct answer | 0.195s |
| Hidden test set 3 | 05 pts | 1 s | Correct answer | 0.197s |
| Test set 4 | 25 pts | 1 s | Correct answer | 0.208s |
| Hidden test set 4 | 05 pts | 1 s | Correct answer | 0.219s |

