# Hong Kong

## Algorithmic problem Desciption 

Given a 2D plane with $n$ trees ($1 \leq n \leq 4 \cdot 10^4$) positioned at coordinates $(x_i, y_i)$ where $|x_i|,|y_i| < 250$, each represented as an open disk with radius $r$ ($1 \leq r < 250$), and $m$ balloons ($1 \leq m \leq 9 \cdot 10^4$) with initial positions $(x_j, y_j)$ and radius $s_j$ where $|x_j|,|y_j|,s_j < 250$, determine for each balloon whether it can be: (1) inflated at its initial position (i.e., the balloon's disk must not overlap with any tree's disk), and (2) moved to a position with sufficient takeoff clearance, where takeoff clearance means all trees must have a distance of at least $r + s_j$ from the balloon's center. The movement path of an inflated balloon must ensure no overlap with any tree disk occurs during transit. Output 'y' if both conditions can be met for a balloon, and 'n' otherwise.


## Solution Approach
This problem can be solved using a priority queue approach for traversing the faces of a Delaunay Triangulation. For each face in the triangulation, we need to determine the maximum size of a balloon that can take off when starting from that face, either by taking off directly or by moving to another face from which takeoff is possible.

The algorithm consists of two main steps:

1. **Initial Face Assignment:** For each face, we assign the maximum clearance value:
   - For infinite faces, this is set to $\infty$ 
   - For finite faces, we use the dual vertex of the Delaunay face (center of the circumcircle) to compute the distance to its closest vertex, which represents the maximum radius of an empty disk that can be placed in this face

2. **Clearance Propagation**: Using a priority queue ordered by clearance values, we propagate clearance information between adjacent faces. For each face:
   - The clearance that can be propagated through an edge is limited by both:
     - The edge length (as the balloon must fit through the edge)
     - The clearance value of the source face
   - The minimum of these two values represents the maximum balloon size that can reach the neighboring face

Finally, for each balloon we check:
1. If it can be inflated at its initial position (distance to nearest tree ≥ balloon radius)
2. If the face containing the balloon's initial position has sufficient clearance for takeoff (either directly or by movement to another face)


## Learnings

- Never use root!
- If there are weird constraints they are usually designed to make things easier when working with distances
- For BFS make sure always reference the current element in the loop