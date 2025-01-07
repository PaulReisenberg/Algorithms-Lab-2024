# Germs

## Solution Approach
This problem clearly calls for a Delaunay Triangulation. The Delaunay Triangulation contains the nearest neighbor graph, which is exactly what we need to determine which growing disks will collide with each other first. To calculate the time at which two disks will collide, we can simply use:
$$
t = \sqrt{\frac{d - 1}{2}}
$$
Additionally, we have a box containing the bacteria. Given that $d_{box}$ is the closest distance to the box, a bacterium will hit the edge of the box in:
$$
t = \sqrt{d_{box} - 0.5}
$$
We must then simply take the smaller of both times for each bacterium, sort them, and return the values at positions $0$, $n/2$, and $n-1$.


## Test Results
| Test Set | Points | Time Limit | Result | Time |
|----------|---------|------------|---------|------|
| 1 | 20 pts | 0.600s | Correct | 0.002s |
| 2 | 20 pts | 0.600s | Correct | 0.053s |
| 3 | 30 pts | 0.600s | Correct | 0.198s |
| 4 | 30 pts | 0.600s | Correct | 0.176s |
**Total Score: 100 points**