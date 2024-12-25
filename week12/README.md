# The Nemean Lion

## Algorithmic Problem Description

We are given a set of points $F$ in the $\mathbb{R}^2$ plane. A subset $T \subseteq F$ is admissible for a distance $d$ if there exists a point $p$ to which every point in $T$ has exactly distance $d$ and every point in $F$ at least distance $d$. 

We may assume:

(1) There is at least one admissible set for some distance in $F$

(2) There is no admissible set of size 4 or more for any distance $d$


Input: $F$ and squared distances $s$ and $a$

Output:
- $a_2$: THe smallest number of pairwise distinct admissible sets of size 2 and distance $d_2$. $d_2$ is the smallest distance such that an admissible set of size 2 exists. 

- $a_3$

- $a_s$ the number of pairwise distinct admissible sets of size two for distance $\sqrt{s}$

- $a_{max}$ the maximum number of pairwise distinct admissible sets of size 2 for any distance $d$

## Solution Approach

To solve this problem, we can use the Voronoi diagram and Delauney Triangulation. 

1. $a_2$: We can compute the smallest distance in the graph. This distance must be $d_2$. The then find all other points in $F$ that are $d_2$ far apart. Using a Maximum Matching on the subgraph with all edges of length $d_2$ we can find the maximum number of pairwise distinct admissible sets of size 2.


2. $a_3$: Because of hint (2) we know that we are looking for vertices of degree 3 and can ignore vertices of higher degrees. We then find a vertex of degree 3 which is closest a point in $F$. This distance is $d_3$ and we must find all other vertices of the Voronoi Diagram that fulfill this property.

3. Each edge in the Voronoi Diagram separates two areas coresponding to two points in $F$. A set of these two points is admissable for all distances in an interval: [distance between the two points/2, distance to the closest verted of the edge). If the interval contains $\sqrt{s}$, these two points can form an admissable set of size two for $\sqrt{s}$. Similar to 1., we use a Maximum Matching to find the largetst number of pairwise distinct admissible sets.

4. 