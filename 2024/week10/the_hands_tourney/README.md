# The Hand’s Tourney

## Problem Description

Given $n$ points representing tent locations in 2D space, each to be assigned to one of $f$ families, requiring at least $k$ tents per family. An assignment is $(f,s)$-reasonable if: (1) each tent belongs to exactly one family, (2) each family gets $\geq k$ tents, (3) tents from different families have squared Euclidean distance $\geq s$. For fixed $k$ and tent positions, solve two queries: (1) given $f_0$, maximize $s$ for an $(f_0,s)$-reasonable assignment, (2) given $s_0$, maximize $f$ for an $(f,s_0)$-reasonable assignment. Constraints: $2 \leq n \leq 9 \cdot 10^4$, $1 \leq k \leq 4$, $f_0 \geq 2$, $kf_0 \leq n$, $0 \leq s_0 \leq 2^{50}$, coordinates $|x|,|y| < 2^{24}$.

### Solution Concept

This problem becomes clearer when we realize that given a minimum distance $s$, all nodes in a connected component must be assigned to the same family. We use Delaunay Triangulation to find these components efficiently. By processing the triangulation edges in ascending order of length, we discover how components merge at different values of $s$. We track components by four size categories (1, 2, 3, ≥4) since $k \leq 4$, and components larger than 4 must still be assigned to one family. At each edge length, we calculate the maximum possible number of families given current components, handling various size combinations in the get_f function. This lets us answer both queries: we update the maximum feasible $s$ whenever we can still form $f_0$ families, and we update the maximum number of families whenever the current edge length is at most $s_0$.


### Test Results


| Test Set          | Points | Time Limit | Result         | Runtime |
|-------------------|--------|------------|----------------|---------|
| Test set 1        | 25 pts | 2 s       | Correct answer | 0.013s  |
| Test set 2        | 25 pts | 2 s       | Correct answer | 0.37s   |
| Test set 3        | 15 pts | 2 s       | Correct answer | 0.319s  |
| Test set 4        | 15 pts | 2 s       | Correct answer | 0.243s  |
| Hidden test set 1 | 05 pts | 2 s       | Correct answer | 0.013s  |
| Hidden test set 2 | 05 pts | 2 s       | Correct answer | 0.37s   |
| Hidden test set 3 | 05 pts | 2 s       | Correct answer | 0.319s  |
| Hidden test set 4 | 05 pts | 2 s       | Correct answer | 0.243s  |