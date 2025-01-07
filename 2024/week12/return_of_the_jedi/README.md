
# Return of the Jedi

## Algorithmic Problem Description

Given a fully connected Graph $G$ find the cheapest Minimum Spanning Tree, that is not the tree obtained by the Kruskal algorithm.

Inerestingly we are able to ignore a lot of information from the problem description. In the story we get the index of Tatoine and Lea's very clear construction algorithm for the MST. We can convince ourselves that that we can ignore this information by a simply case distinction:

- case 1: There is only one unique MST -> The MST we obtain using kruskals algorithm must be the same MST as Lea's.

- case 2: There are more than one MST -> As we will find find an MST different to Lea's the solution must be the same cost as for Lea's MST. We will get to the same solution starting with kurskals MST as we will also find another MST.

## Solution Apporach

1. Find the MST using Kruskals Algorithm and compute its cost. We then store the MST in an adjacency list and furthermore record in a 2d bool vector which edges have been used in the MST.

2. We then iterate over the edges that are not part of the MST and check the following: Given an adge $(u,v)$ not part of the MST, what is the largest edge in the MST on the $u-v$ path? We then compute the difference between this longest edge and the edge $(u,v)$. The idea behind this is that we can build a new ST using $(u,v)$ and leaving out the longest edge from the current MST. If this difference is $0$ we can stop. To do this efficiently, we precompute the maximum edges for every $u,v$ pair.



## My Mistakes

- declared a vairable without initializing it to 0. This lead to undefined behaviour and it took some time to find this mistake. 

## Test Results

| Test Set    | Points | Time Limit | Result         | Runtime |
|-------------|--------|------------|----------------|---------|
| Test set 1  | 40 pts | 2 s       | Correct answer | 0.012s  |
| Test set 2  | 40 pts | 2 s       | Correct answer | 0.788s  |
| Test set 3  | 20 pts | 2 s       | Correct answer | 1.348s  |

**Total Score: 100**