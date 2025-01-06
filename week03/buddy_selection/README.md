# Buddy Selection

## Problem Description

We are given $n$ (even) students. Each student $i$ has exactly $c$ ($\leq 100$) different characteristics. Given the value $f$ we have to answer the question if there exists a paring of students such that every pair shares more than $f$ characteristics.

## Solution Concept

We can solve this problem using Edmond's Maximum Cardinality algorithm. Given a graph $G$ this algorithm will return a pairing of adjacent vertices such that there exists no pairing with more pairs. We construct our graph by connecting every pair of students that shares more than $f$ characteristics. By sorting the characteristics of each student, we can achieve a runtime of $\mathcal{O}(n * c \ log \ c + n^2c)$ instead of $\mathcal{O}(n^2 * c^2)$ for building the graph. What remains is using Edmond's algorithm to check if a pairing of all students is possible. If so, we know that we can achieve a pairing such that every pair has more than $f$ characteristics in common.


### Test Results


| Test Set     | Points | Time Limit | Result         | Execution Time |
|--------------|--------|------------|----------------|----------------|
| Test set 1   | 30 pts | 2 s        | Correct answer | 0.084s         |
| Test set 2   | 40 pts | 2 s        | Correct answer | 0.181s         |
| Test set 3   | 20 pts | 2 s        | Correct answer | 1.417s         |
| bordercases  | 10 pts | 2 s        | Correct answer | 0.083s         |