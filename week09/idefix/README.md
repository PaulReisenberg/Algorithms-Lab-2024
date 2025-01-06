# Idefix

## Problem Description

Given $n$ points (holes) in 2D space to plant trees with radius $r$ where $s=4r^2$, and $m$ points representing buried bones. Each tree casts a circular shadow centered at its hole. Let $P$ be a path between any two points that stays within the union of shadows. The task has two parts: (1) find the maximum number of distinct bones that can be collected along some $P$ using radius $r$, and (2) find the minimum radius $b$ needed to collect at least $k$ bones along some valid path $P$.

### Solution Appraoch

The solution relies on identifying critical radii where connectivity changes occur:
1. When a bone becomes reachable: radius where a bone point enters a tree's shadow
2. When trees become connected: radius where shadows of two trees intersect

We process these events in order of increasing radius using a modified Kruskal's algorithm with connected components. For efficiency, we only consider tree-tree connections from the Delaunay triangulation, as these contain all relevant shortest paths. For each radius:
- Tree-bone events increase bone count for that component
- Tree-tree events merge components and their bone counts
- Part (1): Count maximum bones reachable at radius $r$ where $4r^2=s$
- Part (2): Find minimum radius where $k$ bones become reachable



## Test Results


| Test Set          | Points | Time Limit | Result         | Runtime |
|------------------|---------|------------|----------------|----------|
| Test set 1       | 20 pts  | 1 s        | Correct answer | 0.018s   |
| Hidden test set 1| 05 pts  | 1 s        | Hidden         | -        |
| Test set 2       | 20 pts  | 1 s        | Correct answer | 0.094s   |
| Hidden test set 2| 05 pts  | 1 s        | Hidden         | -        |
| Test set 3       | 20 pts  | 1 s        | Correct answer | 0.028s   |
| Hidden test set 3| 05 pts  | 1 s        | Hidden         | -        |
| Test set 4       | 20 pts  | 1 s        | Correct answer | 0.268s   |
| Hidden test set 4| 05 pts  | 1 s        | Hidden         | -        |