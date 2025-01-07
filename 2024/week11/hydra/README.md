# Lernaean Hydra

## Algorithmic Problem Description

We are given an integer $n$ and a set $S$ of strings. Each string $s \in S$ has length $k$.
We must find a valid sequence of strings $s_0,...,s_{n-1}$ in $S$.
Let $a \oplus b$ denote the string obtained by combining the maximum overlap of two strings, for example "ABCD" $\oplus$ "BCDE" = "ABCDE". Let $\text{merge}(s_0, ..., s_{n-1}) = ((s_0 \oplus s_1) \oplus s_2) \oplus ...$
A valid sequence is a sequence of length $n$ such that:
- $s_i[k-1] = i$
- for each $i \in \{0,...,n-1\}$: $\nexists j \geq |\text{merge}(s_0,...,s_i)|$ with $\text{merge}(s_{i+1}, ..., s_{n-1})[j] = i$

Our task is to minimize $|\text{merge}(s_0, ..., s_{n-1})|$ s.t. $s_0, .., s_{n-1}$ being a valid sequence.

## Solution Approach

This problem can be solved by finding the shortest path in an appropriate graph. Our graph has exactly $n+2$ vertices: a start vertex, an end vertex, and a vertex for each string in $S$. We divide the vertices representing the strings into $n$ groups. Each element in group $i$ contains a string where $s[k-1]=i$ and is connected to each element in group $i+1$ such that the sequence of strings remains valid. The cost associated with each connection is $k$ minus the size of the overlap between the two strings.

## Implementation

The implementation uses Boost's Graph Library (BGL) to create and traverse the directed weighted graph. The core algorithm involves constructing the graph by calculating the valid transitions between strings and their overlaps, then using Dijkstra's shortest path algorithm to find the minimum total length. Two key helper functions, `required_prefix_len` and `prefix_match`, are used to efficiently compute string overlaps and ensure sequence validity. The graph construction is optimized by sorting strings based on their last character and only checking relevant previous strings for valid connections.

## Test Results
| Test Set | Points | Time Limit | Result | Time |
|----------|---------|------------|---------|------|
| 1 | 25 pts | 2.000s | Correct | 0.037s |
| 2 | 25 pts | 2.000s | Correct | 0.039s |
| 3 | 25 pts | 2.000s | Correct | 1.105s |
| 4 | 25 pts | 2.000s | Correct | 1.086s |

**Total Score: 100 points**