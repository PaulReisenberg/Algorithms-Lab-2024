# Algocoön

## Algorithmic Problem Description

Given a graph $G=(V,E)$ representing a sculpture with $n$ figures as vertices and $m$ directed limbs as edges, where each edge $e=(u,v)$ has cost $c_e$. The task is to partition $V$ into two non-empty sets $S$ and $T$, where you take $S$ and pay for cutting limbs originating from your figures (vertices in $S$), while your friend takes $T$ and pays for cutting their limbs. Find the partition minimizing your cost. 

## Solution Appraoch

This problem already screams Min Cut. We know that the Min Cut corresponds to the Max Flow in a graph, thus a solution concept is straight forward. Given the optimal partition $S$ and $T$, we know that the Min Cut is the same between all $s$/$t$ combinations with $s \in S$ and $t \in T$. Thus we know that $0 \in S$ or $0 \in T$ and we can simply check the flow in both directions for every other vertex. 

### Test Results

| Test Set | Points/Time Limit | Result | Execution Time |
|----------|-----------------|--------|----------------|
| 1 | 20 pts / 3 s | Correct answer | 1.205s |
| 2 | 20 pts / 3 s | Correct answer | 1.051s |
| 3 | 20 pts / 3 s | Correct answer | 0.070s |
| 4 | 20 pts / 3 s | Correct answer | 1.160s |
| 5 | 20 pts / 3 s | Correct answer | 0.912s |