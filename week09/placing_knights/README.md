### Solution Concept

The important clue here is that a knight can only strike on fields with opposite color. This there can be no "circle" of odd length and thus we can build a bipartite graph representing which knights conflict. We can use the max flow in this graph to figure out how many knights are in conflict and subtract this value from the total number of possible squares and get our final result.  


### Test Results

| Test Set    | Points | Time Limit | Result         | Execution Time |
|-------------|--------|------------|----------------|----------------|
| Test set 1  | 30 pts | 0.500 s   | Correct answer | 0.001 s       |
| Test set 2  | 35 pts | 0.500 s   | Correct answer | 0.063 s       |
| Test set 3  | 35 pts | 0.500 s   | Correct answer | 0.167 s       |