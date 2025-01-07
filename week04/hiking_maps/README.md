# Hiking Maps

## Problem Description

The problem provides a hiking path defined by $m$ points forming $m-1$ line segments, along with $n$ triangular map sections. Each triangle is specified by 6 points located on its edges (2 points per edge, not at vertices) and includes its boundaries. The task is to find a minimum-length contiguous subsequence of map sections $b$ to $e$ such that every path segment is completely contained within at least one map from this sequence. This defines a bulk purchase of maps costing $e-b$ CHF.

## Solution Appraoch

The first step of the solution was to obtain for each triangle the legs that it fully covered. After that, I used a sliding window approach to find the least amount of triangles to buy to cover the entire hiking path.


## Learnings

Use this to check if a point is within a triangle:

```C++
auto or0 = CGAL::orientation(v1, v2, points[j]);
auto or1 = CGAL::orientation(v2, v3, points[j]);
auto or2 = CGAL::orientation(v3, v1, points[j]);
bool covered = (or0 <= 0 && or1 <= 0 && or2 <= 0) || 
               (or0 >= 0 && or1 >= 0 && or2 >= 0);
```

### Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|--------|------------|--------|----------------|
| 1 | 20 pts | 0.400 s | Correct answer | 0.01s |
| 2 | 20 pts | 0.400 s | Correct answer | 0.021s |
| 3 | 20 pts | 0.400 s | Correct answer | 0.328s |
| 4 | 20 pts | 0.400 s | Correct answer | 0.36s |
| 5 | 20 pts | 0.400 s | Correct answer | 0.237s |