# Asterix in Switzerland

## Problem Description
We are given $n$ provinces with each province having a balance $b_i$. Additionally, we have $m$ debt relations with province $i$ owing $j$ exactly $d_{i,j}$. We must check if there exists a free-standing union of provinces $X$ such that
$\Sigma_{i \in X} b_i > \Sigma_{i \in X, j \notin X} d_{i,j}$
## Solution Approach
Without thinking much about the problem, you could get the idea to model this problem as a max flow problem, without really knowing where this would lead to. We could simply create the graph as specified by $d_{i,j}$, and connect each province with a positive $b_i$ to the source and the ones with a negative balance to the sink. Now we need to check if the max flow is equal to the total sum of positive balances; if not, we know that there exists such a union. Remarkably, this works. But why?

## Proof Sketch

Let's assume that there is a union $X$ for which our condition holds. Let $F_X$ be the total flow that flows into $X$ directly from the source. If in the best case, all the nodes in $X$ are connected with infinite capacity, we would be able to drain $\Sigma_{i \in X, b_i < 0} |b_i|$ of $F_X$ via nodes from $X$. Now we are left with $\Sigma_{i \in X} b_i$. In the best case, we are able to route
$\Sigma_{i \in X, j \notin X} d_{i,j}$ flow via vertices outside of $X$ to the sink. But because we assume $X$ to be a free-standing union, we know that $\Sigma_{i \in X} b_i > \Sigma_{i \in X, j \notin X} d_{i,j}$ and thus there is at least one unit of flow that we cannot route to the sink and therefore the max flow must be less than the total sum of positive balances.

To show the implication in the other direction, let's assume that the max flow $<$ $\Sigma_{b_i > 0} b_i$. Now, if just $\Sigma_{i <n} b_i >0$, simply $X=\{0,...,n-1\}$ would be a free-standing union. Let's assume that is not the case. This means that there are some edges to the sink that are not fully utilized. We now build the following union: $X = \{i  | flow((i,sink)) = capacity((i, sink))\}$. Now we only need to show that $X$ is a free-standing union. Because we know that the max flow $<$ $\Sigma_{b_i > 0} b_i$, some units of flow that go into $X$ from the source are unable to flow to the sink. And because we know that all vertices outside of $X$ still have capacity free to the sink, we know $\Sigma_{i \in X} b_i > \Sigma_{i \in X, j \notin X} d_{i,j}$ must hold.


## Test Results


| Test Set | Points | Time Limit | Result | Actual Time |
|----------|---------|------------|---------|-------------|
| 1 | 20 pts | 1 s | Correct answer | 0.0s |
| 2 | 20 pts | 1 s | Correct answer | 0.229s |
| 3 | 20 pts | 1 s | Correct answer | 0.149s |
| 4 | 40 pts | 1 s | Correct answer | 0.232s |

Total Score: 100