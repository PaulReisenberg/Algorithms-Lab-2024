
# Planet Express

## Problem Description

Given a directed weighted graph $G=(V,E)$ with $|V|=n$ vertices and $|E|=m$ edges, representing a galaxy where vertices are planets and edge weights are travel times in microseconds. There are $k$ warehouses located at vertices $\{0,\ldots,k-1\}$ and the target destination is always at vertex $n-1$. Additionally, $T$ planets form a teleportation network where teleportation between linked planets $u$ and $v$ takes $t(u)$ microseconds, where $t(u)$ is the number of planets linked to $u$. Two planets are considered linked if they are mutually reachable without using teleportation. The task is to determine if it's possible to deliver from any warehouse to vertex $n-1$ within 1 second (1,000,000 microseconds) and if so, find the minimum delivery time. A planet pair is considered linked if there exists a bidirectional path between them without using teleportation.

## Solution Appraoch

To solve this problem, we first compute the teleportation links between nodes in the teleportation network. We use a BFS approach and maintain a set of reachable teleportation nodes for each teleportation node. This optimization allows us to skip BFS traversal for previously computed nodes and instead directly add their known linked nodes to the current node's set. For each teleportation link, the weight is calculated as the total number of linked nodes minus 1.

Because we have to choose the closest warehouse to the node $n-1$ it makes more sense to use Dijkstra in reverse, as we will receive a distance map containing the distance **from** one node to all the other nodes. We simply reverse all edges in the graph and compute the distance from the target node to all warehouses using Dijkstra and pick the nearest one and check if it is closer than 1,000,000.
