# Ludo Begman

## Algorithmic Problem Description

We are given a bipartite graph with two types of edges. An edge $e \in E$ is either difficult or not difficult, e.g. $type(e) \in \{difficult, \neg difficult\}$ and has a risk associated with it risk $(e) \in \mathbb{N}_0$. Additionally, we are given two integers $p$ and $l$. We must now find a subset $S \subseteq E$ with the following attributes:
- $|S| = p$

- $|\{ e \ | \ e \in S \land \text{type}(s) = \neg difficult \}|$

- $\Sigma_{e \in S} \ \text{risk}(e)$ is minimized

## Solution Approach

We immediately notice that the input bounds are just low enough to make a Max Flow Min Cost approach feasible. What do we know about our graph structure already? 
- The flow should be $p$ as this is the amount of matches we must play. We can enforce this by setting the sum of capacities of outgoing edges to $p$.
- Each team gets a difficult and non-difficult node. The possible matches lead to edges between these nodes.
- Because we need to enforce that every team plays $l$ non-difficult matches, we connect the source to the non-difficult node for each team from the east and set the capacity to $l$. We do the same for the sink and the teams from the west.
- lastly, we connect the source to all team nodes from the east via an intermediary node that has the capacity $p - e \cdot l$. We do the same for the players from the west and the sink.

If the flow in this network is below $p$, we know that no schedule is possible. If the flow is equal to $p$ we know that for each team at least $l$ easy matches have been found due to the capacity restrictions.

## Test Results

Here's the test results table formatted for your README.md:

| Test Set | Points | Time Limit | Runtime |
|----------|--------|------------|---------|
| Test set 1 | 20 pts | 2 s | 0.074 s |
| Test set 2 | 20 pts | 2 s | 0.410 s |
| Test set 3 | 20 pts | 2 s | 0.695 s |
| Test set 4 | 20 pts | 2 s | 1.174 s |
| Hidden test set 1 | 5 pts | 2 s | Hidden |
| Hidden test set 2 | 5 pts | 2 s | Hidden |
| Hidden test set 3 | 5 pts | 2 s | Hidden |
| Hidden test set 4 | 5 pts | 2 s | Hidden |

**Total Score: 80**

