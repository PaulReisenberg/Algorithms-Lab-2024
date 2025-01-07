# Asterix and the Tour of Gaul

## Algorithmic Problem Description

We are given locations $s_0, ..., s_{n-1}$ and capacities $c_0, ..., c_{n-2}$. Additionally, we get $m$ food items $F$ with a start location $a_i$, an end location $b_i$ and a significance $d_i$.

We must find a mapping $S:F \mapsto \{0,1\}$ such that:

max $\Sigma_{j \in F: S(j) = 1} \ \ d_j $

$ | \{j \in F: S(j)=1 \land a_j \leq i \land b_j > i\} | \leq c_i \quad \forall i \in \{0,n-1\}$ 



## Solution Appraoch


This problem was one of the hardest ones because it was not directly obvious to me that this could be solved using Max Flow Min Cost. Once you realise that this can be solved with Max Flow, finding an algorithm that solves this problem is fairly easy. However, finding an algorithm that is fast enough to pass all the tests, not so much.

### Slow Solution

For each location, we introduce two nodes. One of them, the in_node, is connected to the source and the other one, the out_node, to the sink. We connect the out_nodes according to the capacities. For each food item, we create two edges. One that goes directly to the out_node of $b_i$. This edge represents $S(b_i)=0$ the other one goes to the out node of $a_i$ representing $S(b_i)=1$. This unit of flow must then take the path from $a_i$ to $b_i$ along the out nodes, which have the according capacity constraints. The cost of the first edge is then some value $max$ and that of the second edge $max - d_i$. This works because each unit of flow that comes in has exactly one "designated" final edge to the sink. This ensures that a unit of flow can't flow to the sink before $b_i$. This works, however it is too slow.

### Fast Solution

Here we only need $n$ nodes + source and sink. We connect the source to $s_i$, $s_{i+1}$ to the sink and $s_i$ to $s_{i+1}$ for each $i \leq n-2$ all with capacity $c_i$. The edges from the source and to the sink get cost $0$ and the edge from $s_i$ to $s_{i+1}$ gets $max\_cost$. Now, for each food we add an edge from $a_j$ to $b_j$ with the capacity $1$ and cost $(b_i - a_j) * max\_cost - d_j$. The final results are then $flow * max\_cost - cost$. Now why the hell does this work?

Let's assume there are no products to be delivered. We can imagine the following path for the flow. For each node $i$ exactly $c_i$ is coming in from the source. It then flows to $i+1$ and then flows from $i+1$ to the sink. The max flow of this network is simply $\Sigma_{i \leq n-2} \ c_i$. Now let's add a product to be delivered from $i$ to $j$ with significance $d$. If we now route one unit of flow along the edge from $i$ to $j$ one unit of flow less is flowing to the sink at $i+1$. To make up for this, we need to route one unit which previously went source -> $i+1$ -> $i+2$ -> sink directly from $i+1$ to the sink to fill the vacuum created. This again creates a vacuum at the node $i+2$ and this continues up until $b_j$. This is only possible if the capacities $c_i,.., c_{j-1}$ allow for it, thus we can think of the flow from $i$ to $i+1$ as the remaining capacity of that path. The cost is now reduced by $d$. 



## Test Results


| Test Set | Points | Time Limit | Result | Time |
|----------|---------|------------|---------|------|
| 1 | 20 pts | 2 s | ✓ | 0.063s |
| 2 | 20 pts | 2 s | ✓ | 1.173s |
| 3 | 20 pts | 2 s | ✓ | 1.171s |
| 4 | 20 pts | 2 s | ✓ | 0.113s |
| 5 | 20 pts | 2 s | ✓ | 1.531s |
