# Hermione Granger

## Problem Description

The problem requires allocating $f$ ml of Felix Felicis potion among $d$ members to gather information about three targets. Each member needs $f_j$ ml per hour to interrogate their nearest Slytherin student from $s$ students at given 2D coordinates. During each hour, a Slytherin student $i$ provides $(m_i,c_i,g_i)$ information about three targets. The goal is to determine if sufficient total information $(m,c,g)$ can be gathered within 24 hours by optimally distributing the potion. The problem has three variants with increasing complexity based on constraints on $s$ and equality of information rates.


## Solution Appraoch

Solution uses linear programming with the following approach:
1. For each DA member, find their closest Slytherin student using Delaunay Triangulation
2. For each Slytherin student, keep only the DA member with minimum potion requirement ($f_j$) who can reach them
3. Create LP with variables representing hours spent by each viable DA-Slytherin pair:
  - Objective: minimize total potion usage ($\sum f_j \cdot hours_j$)
  - Constraints: 
    - Total information gathered for each target $\geq$ required $(m,c,g)$
    - Total time $\leq 24$ hours
    - All variables $\geq 0$
4. Output "L" if solution exists with objective $\leq f$ (total potion), "H" otherwise

## Test Results

| Test Set          | Points | Time Limit | Time    | Status          |
|-------------------|--------|------------|---------|-----------------|
| Test Set 1        | 30     | 1s        | 0.285s  | ✓ Correct      |
| Test Set 2        | 30     | 1s        | 0.725s  | ✓ Correct      |
| Test Set 3        | 20     | 3s        | 2.775s  | ✓ Correct      |
| Hidden Test Set 1 | 5      | 1s        | 0.303s  | ✓ Correct      |
| Hidden Test Set 2 | 5      | 1s        | 0.756s  | ✓ Correct      |
| Hidden Test Set 3 | 10     | 3s        | 2.680s  | ✓ Correct      |
