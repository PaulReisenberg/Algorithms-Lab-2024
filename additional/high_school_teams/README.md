
# High School Teams

## Algorithmic Problem Description


Given a set of $n$ students $S$ with skill levels $l_i$ (possibly negative) and a non-negative integer $k$, find the number of distinct fair team assignments where $A, B \subseteq S$ are disjoint subsets (teams A and B) such that $\sum_{i \in A} l_i = \sum_{j \in B} l_j$ (equal team skills) and $|S \setminus (A \cup B)| \leq k$ (at most $k$ students unassigned). Teams can be empty (counting as zero skill) and unassigned students are considered referees. Importantly we do not count the same team player assigments to $A$ and $B$ twice meaning $A =\{1\}, B=\{2\}$ and $A =\{2\}, B=\{1\}$ is considered the same assignment.

Input constraints: $1 \leq n \leq 22$, $0 \leq k \leq n$, and $\sum_{i=0}^{n-1} |l_i| < 2^{31}$. The problem involves multiple test cases $t \leq 10$, and the solution for each case must fit within a signed 64-bit integer.

## Solution Approach

This is an NP-hard problem (with $n \leq 22$) that we solve using a Split and List strategy. The key challenge is handling three groups: team A, team B, and referees (unassigned players), while maintaining equal team strengths. 

We split the input into two halves and process each independently. For each half:
1. Generate all possible referee combinations for $0$ to $k$ referees using binary representation (e.g., for 4 players and $k=3$: 0000, 1000, 1100, etc.)
2. For the first half:
   - For each referee combination, compute all possible team A/B assignments
   - Store the absolute skill difference between teams in a map: $\text{diff} \rightarrow \text{count}$
3. For the second half:
   - Similarly generate all combinations
   - For each combination, check if a complementary difference exists in the first half (where total referees $\leq k$)
   - Account for symmetry by dividing non-zero differences by 2

The solution uses bit manipulation for efficient combination generation and mapping for fast lookups, running in $O(2^{n/2})$ time.