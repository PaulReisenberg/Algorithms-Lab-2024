### Explanation

In my solution, I use a greedy approach to help Bond deactivate the bombs safely. First, I sort the bombs by their explosion times to prioritize the most urgent ones. I traverse the bombs in order of their explosion times. For each bomb I must defuse all bombs it depends on first and here the order does not matter which allowes use to use a simple greedy strategy to solve this problem.

### Test Results

| Test Set          | Points | Time Limit | Result         | Execution Time |
|-------------------|--------|------------|----------------|----------------|
| Test set 1        | 20 pts | 1 s       | Correct answer | 0.000 s       |
| Test set 2        | 20 pts | 1 s       | Correct answer | 0.011 s       |
| Test set 3        | 20 pts | 1 s       | Correct answer | 0.024 s       |
| Test set 4        | 20 pts | 1 s       | Correct answer | 0.204 s       |
| Hidden test set 1 | 05 pts | 1 s       | Correct answer | 0.000 s       |
| Hidden test set 2 | 05 pts | 1 s       | Correct answer | 0.011 s       |
| Hidden test set 3 | 05 pts | 1 s       | Correct answer | 0.024 s       |
| Hidden test set 4 | 05 pts | 1 s       | Correct answer | 0.205 s       |