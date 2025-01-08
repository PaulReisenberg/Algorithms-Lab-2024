# The Nemean Lion

## Algorithmic Problem Description

We are given a set of points $F$ in the $\mathbb{R}^2$ plane. A subset $T \subseteq F$ is admissible for a distance $d$ if there exists a point $p$ to which every point in $T$ has exactly distance $d$ and every point in $F$ at least distance $d$. 

We may assume the following:

(1) There is at least one admissible set for some distance in $F$

(2) There is no admissible set of size 4 or more for any distance $d$


Input: $F$ and squared distances $s$ and $a$

Output:
- $a_k$: The smallest number of pairwise distinct admissible sets of size $k \in \{2,3\}$ and distance $d_k$. $d_k$ is the smallest distance such that an admissible set of size $k$ exists. 

- $a_s$ the number of pairwise distinct admissible sets of size two for distance $\sqrt{s}$

- $a_{max}$ the maximum number of pairwise distinct admissible sets of size 2 for any distance $d$

## Solution Approach


I shamelessly took inspiration from [here](https://github.com/quantaji/ethz-algorithm-lab-2022-self-solution/blob/main/week12/04_the_nemean_lion/src/main.cpp#L64). 

- $a_2$: Let $d_2$ be the minimal distance such that an admissible set of size 2 exists. We know that the number of those sets corresponds to the number of edges in the distance graph with the minimum distance. This is intuitively clear. Assume we have that shortest distance between $a$ and $b$ and the midpoint $m$ between those two points. If there was another point $c$ closer to $m$ than $a$ and $b$, making the set $\{a,b\}$ infeasible, then $|m-b|$ would be smaller than $|a-b|$ contradicting our assumption. Because the Delaunay Triangualtion contains the Nearest Neighbor Graph, we can simply iterate through all edges and count how often we encounter the smallest one.

- $a_3$: Here we can use our knowledge about the Voronoi Diagram and its relation to the Delaunay Triangualtion. From the problem description, we know that there are no vertices of degree $4$ or larger in the Voronoi Diagram; thus, for each finite face in the Delaunay Triangulation, there exists a vertex in the Voronoi Diagram and vica versa. The vertex in the Voronoi diagram corresponds to the **only** point with the same distance to all three vertices of the face, and because it is a vertex of the Voronoi diagram, we know that no other vertex is closer to it than the three vertices of the face. Because of these properties, we know that this is an admissible set for the distance from the voronoi vertex to one of the face vertices. As for $a_2$ we simply have to record how often we encounter the shortest distance.

- $a_s$: The only possible feasible sets of size $2$ are nodes that are connected in the Delaunay Triangulation. [Why?] For each pair, we need to figure out the $d_{min}$ and $d_{max}$ for which those two trees remain a feasible set. Assuming that the nodes $u$ and $v$ form a feasible set, we know that there is an edge in the Voronoi Diagram that separates them. This Voronoi line can be infinite; this is the case iff the edge $u$ to $v$ is at the edge of the triangulation (one of the adjacent faces is infinite). Otherwise, $d_{max}$ is bounded by the maximum distance to one of the ends of that line. For $d_{min}$ there are two cases: (1) the edge of the Voronoi diagram intersects the edge between $u$ and $v$, (2) The edges do not intersect. This can be easily checked if we check is the midpoint of $u$ and $v$ is closer to another vertex in the triangulation; if so, then case (2) applies; otherwise, the distance to this midpoint is $d_{min}$. If we have computed all these intervals, we only need to check how many of them contain the value $s$.

- $a_{max}$ Using our computed intervals from the previous query, we can also solve this task. We create a list containing all unique $d_{min}$ and $d_{max}$ values. For each value $d_i$ we record how many intervals we enter by setting $s$ to $d_i$ and how many intervals we will leave once we set $s > d_i$. With a simple traversal, we will be able to get the maximum number of feasible sets of size $2$.


## Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| 1 | 30 pts | 2 s | Correct answer | 0.898s |
| 2 | 30 pts | 2 s | Correct answer | 0.858s |
| 3 | 20 pts | 2 s | Correct answer | 0.771s |
| 4 | 20 pts | 2 s | Correct answer | 0.773s |
| **Total** | **100 pts** | - | - | - |
