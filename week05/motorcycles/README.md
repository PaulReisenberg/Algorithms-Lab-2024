## Solution Concept: The Biker Problem

The solution hinges on understanding one fundamental principle that makes the implementation straightforward. The key is recognizing how path intersections determine which bikers continue and which stop.


### Rule 1: Direct Intersections
When two bikers' paths meet, the biker with the smaller absolute slope continues while the other stops.

### Rule 2: Extended Intersections
A biker will not continue indefinitely if there exists another biker who:
- Has a smaller absolute slope
- Has a path that would intersect (even if they never actually meet due to other stops)

#### Illustration of Concept

Consider two bikers whose paths intersect: A (red) and B (green), where B has a smaller absolute slope than A. Without loss of generality let B be above A. It follows that A's slope must be > 0.

Let's attempt to place a third biker (C) to stop B before A encounters B's path. If the slope B is 0 there is nothing we can do. So lets assume it is not 0.

For our biker C to things must hold:

1. The absolute slope of C must be less than that of B so the we can stop B

2. C must start above A, otherwise we cant reach B before A and B intersect.

We can now place the biker C so that B and C intersect before A and B intersect. We sucessfully stop B from riding, however C starts above A and has a smaller slope than B thus also a smaller slope than A and will after stoping B also stop A from riding forever.

## Algorithm Implementation

We simply iterate over all tracks twice and check if a line from below cuts a biker of or a line from above cuts a biker off.

## Test Results

| Test Set           | Points | Time Limit | Result         | Runtime |
|-------------------|--------|------------|----------------|---------|
| Test set 1        | 20 pts | 4 s       | Correct answer | 0.013s  |
| Hidden test set 1 | 05 pts | 4 s       | Correct answer | 0.013s  |
| Test set 2        | 20 pts | 4 s       | Correct answer | 0.041s  |
| Hidden test set 2 | 05 pts | 4 s       | Correct answer | 0.041s  |
| Test set 3        | 20 pts | 4 s       | Correct answer | 0.15s   |
| Hidden test set 3 | 05 pts | 4 s       | Correct answer | 0.15s   |
| Test set 4        | 20 pts | 4 s       | Correct answer | 1.041s  |
| Hidden test set 4 | 05 pts | 4 s       | Correct answer | 1.041s  |