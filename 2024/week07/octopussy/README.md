# Octopussy

## Problem Description

Given $n$ balls arranged in a tree where ball $j$ rests on balls $2j+1$ and $2j+2$ for $j \in \{0,...,\frac{n-3}{2}\}$, and balls $\{\frac{n-1}{2},...,n-1\}$ are on the ground. Each ball $i$ contains a bomb with timer $t_i$. It takes 1 minute to deactivate a bomb, and a ball's bomb must be deactivated after its supporting balls' bombs. Find a deactivation order $\pi$ where $\pi(i) < t_i$ (deactivate before explosion) and $\pi(x) < \pi(y)$ if $B_y$ supports $B_x$, or report impossible. 

### Solution Appraoch

We can solve this problem with a simple greedy approach, recognizing that the bomb that explodes next has to be defused as soon as possible. First, I sort the bombs by their explosion times to prioritize the most urgent ones. I traverse the bombs in order of their explosion times. For a bomb $x$ that explodes next, I must defuse all bombs that it depends on first, and here the order does not matter. This is because we know that no bomb $x$ depends on will explode before $x$ does. This simple greedy strategy allows us to solve this problem.


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