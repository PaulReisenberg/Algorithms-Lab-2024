### Solution Concept

The solution uses a sliding window approach combined with dynamic programming. For each waterway, it iterates through the islands using two pointers, left and right, to create windows of consecutive islands. It keeps track of the sum of men required for the current window. When this sum equals k, it updates the maximum score. The algorithm also maintains a map to store partial sums and their corresponding scores. This allows for efficiently combining results from different waterways. As it processes each waterway, it checks if the current partial sum can be combined with a complementary sum from a previously processed waterway to reach exactly k men. This approach allows for finding valid plans that span multiple waterways without explicitly checking all possible combinations.

### Test Scorese


| Test Set           | Points | Time Limit | Result          | Execution Time |
|--------------------|--------|------------|-----------------|----------------|
| Test set 1         | 20 pts | 2 s        | Correct answer  | 0.502s         |
| Hidden test set 1  | 05 pts | 2 s        | Correct answer  | 0.505s         |
| Test set 2         | 20 pts | 2 s        | Correct answer  | 0.604s         |
| Hidden test set 2  | 05 pts | 2 s        | Correct answer  | 0.606s         |
| Test set 3         | 20 pts | 2 s        | Correct answer  | 0.605s         |
| Hidden test set 3  | 05 pts | 2 s        | Correct answer  | 0.575s         |
| Test set 4         | 20 pts | 2 s        | Correct answer  | 0.663s         |
| Hidden test set 4  | 05 pts | 2 s        | Correct answer  | 0.689s         |
