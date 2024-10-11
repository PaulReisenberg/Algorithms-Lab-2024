### Solution Concept

This problem is similar to the hit problem. We have a raw with a starting point and infinite length and a set of segments. To be returned is the closest intersection point of the ray with any segment. This problem is simply solved by first checking for the first intersection with any segment. Once this segment has been found we can replace our ray by a segment from the starting point to the intersection point we just found as we are only interested in further intersection points that are closer than the one we just found. We continue this approach until we have checked all segments.

### Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|--------|------------|--------|----------------|
| 1 | 15 pts | 1.000 s | Correct answer | 0.006s |
| 2 | 15 pts | 1.000 s | Correct answer | 0.055s |
| 3 | 15 pts | 1.000 s | Correct answer | 0.068s |
| 4 | 15 pts | 1.000 s | Correct answer | 0.054s |
| 5 | 10 pts | 1.000 s | Correct answer | 0.181s |
| 6 | 10 pts | 1.000 s | Correct answer | 0.062s |
| 7 | 10 pts | 1.000 s | Correct answer | 0.053s |
| 8 | 10 pts | 0.200 s | Correct answer | 0.053s |