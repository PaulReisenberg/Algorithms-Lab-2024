# Asterix and the Chariot Race

## Algorithmic Problem Description

We are given a graph $G$ with vertices $V$ (cities) and undirected edges $E$ (stages of a race). Each vertex $i$ is associated with a cost $c_i$. We must find a mapping $S: V \rightarrow \{0,1\}$ that minimizes $\Sigma_{i} \ c_i S(i)$ given that for each $i$ either $S(i) = 1$ or $\exists \ \{i,j\} \in E$ with $S(j)=1$.


## Solution Approach

The first idea that comes to mind, is to model this problem as a max flow min cost problem. However as we can have up to $10^5$ cities this approach becomes infeasable. 

As we know that each city is part of the race and there are only n-1 stages (edges), we know that the graph resulting from connecting all cities that "share" a stage must be a tree. With this insight, let's try to find a recursive definition of the problem that allows us to solve the problem of the tree given the solution of the problem for the subtrees.

Assume we have the root $s$ and the subtrees $s_0, .., s_k$. 

Let $p_0(x)$ be the minimum price we have to pay to "save" all cities in the subtree starting at $x$.

Let $p_1(x)$ be the minimum price we have to pay to "save" all cities in the subtree starting at $x$ given that we fix the roads in $x$.

Let $p_2(x)$ be the minimum price we have to pay, to save all cities in the subtree starting at x given that we do not care about the fate of city $x$. 

We can now recursively define our problem as:

$$
p_0(s) = min \Big (
c_s + p_2(s_0) + .. + p_2(s_k)
\ \ , \ \ min_{i \in [0,..,k]}(p_0(s_0) + ... + p_1(s_i)) + ... + p_0(s_k) \Big) 
\\
\text{} \\
\text{} \\
p_1(s) = c_s + p_2(s_0) + ... + p_2(s_k) \\
\text{} \\
\text{} \\
p_2(s) = min \Big ( c_s + p_2(s_0) + ... + p_2(s_n) \ \ , \ \ p_0(s_0) + ... + p_0(s_k) \Big )
$$

Now we only need to implement it and that's it! The value we are interested in is $p_0(0)$.


## Learnings

- really nice function: #include <numeric> -> accumulate(vec.begin(), vec.end(), init_val);
- Formalizing the problem first really helps


## Test Results


| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| 1 | 25 pts | 3 s | Correct answer | 0.142s |
| 2 | 25 pts | 3 s | Correct answer | 0.154s |
| 3 | 25 pts | 3 s | Correct answer | 0.154s |
| 4 | 25 pts | 3 s | Correct answer | 2.255s |

**Total Score: 100**