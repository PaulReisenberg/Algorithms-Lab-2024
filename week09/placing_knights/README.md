# Placing Knights

## Problem Description

How many non-conflicting knights can we place on an $n \times n$ chess board with some of the fields removed.

## Solution Approach


The important clue here is that a knight can only strike on fields with opposite color. This means that a graph where the vertecies represent fields on the board and edges connect fields where two knights would threaten each other is bipartite. We build this graph and connect every back field to the source and every white field to the sink. Every edge gets capacity $1$. To get the total number of knights we can place, we only need to subtract the Max Flow in this network from the total number of squares.

Why does this work? Assume we place a knight on every square. How many do we need to take away until there are no two knights threating eachother? Exactly $max \ flow$ many. 


### Test Results

| Test Set    | Points | Time Limit | Result         | Execution Time |
|-------------|--------|------------|----------------|----------------|
| Test set 1  | 30 pts | 0.500 s   | Correct answer | 0.001 s       |
| Test set 2  | 35 pts | 0.500 s   | Correct answer | 0.063 s       |
| Test set 3  | 35 pts | 0.500 s   | Correct answer | 0.167 s       |