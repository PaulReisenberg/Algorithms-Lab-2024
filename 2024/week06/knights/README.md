# Knights

## Problem Description
In a grid layout, knights start at different intersections. When a knight moves through a hallway segment, it collapses behind them and can't be used again. Each intersection can be used by up to C knights before collapsing, with knights never arriving at intersections simultaneously. All hallway segments can only be used once. The grid has dimensions m (columns, west to east) and n (rows, north to south), with all hallways connected to exits at their ends.

## Solution Approach
We can model this problem as a Max Flow problem. We simply construct a graph with the same grid layout and give capacities of 1 to all edges and capacity C to all intersections. Then connect each intersection on the edge to the sink with capacity 1. Important: The intersections at the edges of the grid have to be connected to the sink with capacity 2. To simulate a knight, we connect an edge from the source to the position of the knight with capacity 1.

## Test Results
| Test Set | Points | Time Limit | Result | Actual Time |
|----------|---------|------------|---------|-------------|
| 1 | 40 pts | 1 s | Correct answer | 0.122s |
| 2 | 40 pts | 1 s | Correct answer | 0.108s |
| 3 | 20 pts | 1 s | Correct answer | 0.116s |

Total Score: 100
