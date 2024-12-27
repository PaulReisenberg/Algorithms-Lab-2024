# Beach Bars

## Algorithmic Problem Description

We are given a set of $n$ integers $P$ and we must find $max_{x} |\{p \in P \ | \ p \in [x-100, x+100] \}|$.

## Solution Appraoch

This problem can be solved using a simple sliding window appraoch. We first sort the values and then use a sliding window appraoch to find all intervals of size 200 that contain the maximum number of integers. We use two pointers if the interval is too large, we move the left pointer, if the interval is smaller than 200 we move the right pointer.

## Test Results

| Test Set | Points | Time Limit | Result | Execution Time |
|-----------|---------|------------|---------|----------------|
| 1 | 20 pts | 1 s | Correct | 0.001s |
| 2 | 20 pts | 1 s | Correct | 0.002s |
| 3 | 60 pts | 1 s | Correct | 0.378s |
| **Total** | **100/100** | - | - | - |