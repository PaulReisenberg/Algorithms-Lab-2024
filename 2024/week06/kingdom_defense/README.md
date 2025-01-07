# Kingdom Defense
## Problem Description
We are given a graph with directed edges and $l$ locations. Each vertex has a certain number of soldiers stationed there and a certain demand for soldiers to be stationed there. Additionally, the edges have certain minimum and maximum bounds on how often each path must be used.

## Solution Approach
We can model this problem as a Max Flow problem. Each location becomes a vertex in the graph and is connected to the source with capacity equal to the number of soldiers available, and to the sink with capacity equal to the number of soldiers needed to defend this location. Each edge is modeled by two nodes: an in_node and an out_node. The in_node is connected to the sink with capacity equal to the number of times this path must be traveled. The in_node is then connected to the out_node with capacity max_bound - min_bound. The out_node is connected to the source with the same capacity as the in_node. The out_node is then connected to the target location. All conditions can be fulfilled if the Max Flow equals the sum of demands at the edges and locations. This works but is not fast enough...

## Optimization
We can group the in and out nodes of the paths together with the source and target location. This allows us to save many additional nodes and edges. We then compute the net supply/demand of the node and connect that node only to the sink or the source depending on its sign.

## Learnings
Unused nodes significantly impact runtime performance!

## Test Results
| Test Set | Points | Time Limit | Result | Actual Time |
|----------|---------|------------|---------|-------------|
| 1 | 20 pts | 5 s | Correct answer | 1.37s |
| 2 | 20 pts | 5 s | Correct answer | 0.472s |
| 3 | 30 pts | 5 s | Correct answer | 1.551s |
| 4 | 30 pts | 5 s | Correct answer | 1.366s |
Total Score: 100
