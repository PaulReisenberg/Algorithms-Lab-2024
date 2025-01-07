# Iron Islands

## Algorithmic Problem Description

We are given a Graph $G$ with vertecies $V = \{0,...,n-1\}$ and undirected edges $E$. This Graph is a tree with the constaint that only vertex $0$ can have more than $2$ neighmors. This induces a "star" shape with $0$ in the middle and paths going outwards. We know that there are $w$ such paths. Each vertex $v$ has a value $c_v$ assiciated with it. Given the number $k$ we must find the longest path in the graph $v_0$ to $v_m$ such that:

$$\Sigma_{i=0}^m \ \ c_{v_i} = k$$


## Solution Concept

To solve this problem, we use a sliding window approach. We start at the end of each water way moving inwards with two pointers. Once the inner pointer reaches the vertex $0$ we stop right before and only move the outer pointer inwards step by step. For each step we record the length and the sum of values and store them in a hash map length -> sum of values. For the previous water ways for which we have done the same we canefficiently check if we combine paths. This approach allows for finding valid plans that span multiple waterways without explicitly checking all possible combinations.

## Test Scorese


| Test Set           | Points | Time Limit | Result          | Execution Time |
|--------------------|--------|------------|-----------------|----------------|
| Test set 1         | 20 pts | 2 s        | Correct answer  | 0.502s         |
| Hidden test set 1  | 05 pts | 2 s        | Correct answer  | 0.505s         |
| Test set 2         | 20 pts | 2 s        | Correct answer  | 0.604s         |
| Hidden test set 2  | 05 pts | 2 s        | Correct answer  | 0.606s         |
| Test set 3         | 20 pts | 2 s        | Correct answer  | 0.605s         |
| Hidden test set 3  | 05 pts | 2 s        | Correct answer  | 0.575s         |
| Test set 4         | 20 pts | 2 s        | Correct answer  | 0.663s         |
| Hidden test set 4  | 05 pts | 2 s        | Correct answer  | 0.689s         |
