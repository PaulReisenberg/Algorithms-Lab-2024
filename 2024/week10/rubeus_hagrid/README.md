# Rubeus Hagrid

## Problem Description

Given a tree with node $0$ as root and $n$ chambers, each containing $g_i$ galleons that disappear at a rate of 1 per second. Edges represent tunnels with length $\ell$ taking $\ell$ seconds to traverse. A niffler starts at node $0$, must visit all nodes collecting remaining galleons (at least 1 guaranteed per first visit), can use each edge at most twice, and must return to $0$. Find maximum galleons collectable.

## Solution Appraoch

This task seems daunting. Let's try to simplify the task by starting at node $0$ and asking ourselves which subtree should we visit first, second, third and so on. Well, it would help to know how many gallons we would be able to collect in each subtree and how long it would take us to do so. Let's generalize the case and assume war is at node $x$ with $k$ subtrees, and we already spend $t$ seconds to get to $x$. To answer the question in which order we should visit the subtrees, let's assume we have the following three pieces of information:

1. $g_i^x$: If we visit subtree $i$ first, how many gallons can we get from this subtree?

2. $t_i^x$: How many seconds would it take us to reach the node $x$ again so that we can visit the next  

3. $c_i^x$: How many chambers are in the subtree $i$ 

This information is already enough to answer the question of which subtree to visit next. Let's assume we simply pick the order $s_1^x, ..., s_k^x$. The number of gallons we will get is:


$$
\Sigma_{i=1}^k \ \big ( \ g_i^x \ - \ \Sigma_{j=1}^{i-1} \ ( t_j^x \cdot c_i^x) \ \big )
\quad
=
\quad
\Sigma_{i=1}^k \ g_i^x \ - \ \Sigma_{i=1}^k \ \Sigma_{j=1}^{i-1} \ ( t_j^x \cdot c_i^x)
$$

We can see that the only thing we can influence with the order is the second part of the term, describing the gallons we lose by visiting other subtrees first. 

We should visit $i$ before $j$ iff we lose more in $i$ by going to $j$ first than we would lose in $j$ by going to $i$ first:

$$i \geq_g j \quad \text{iff} \quad t_j^x \ c_i^x \geq t_i^x \ c_j^x \cdot  $$ 

And that's already it. We do not have to take into account that some $g_i^x$ might be $0$ because we know, from the problem description, that that will never happen.


## Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| 1 | 30 pts | 3 s | Correct answer | 0.012s |
| 2 | 30 pts | 3 s | Correct answer | 0.391s |
| 3 | 30 pts | 3 s | Correct answer | 0.367s |
| 4 | 10 pts | 3 s | Correct answer | 0.451s |