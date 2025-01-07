# Severus Snape

## Algorithmic Problem Description
We are given a set of potions $\mathcal{P} \subset \mathbb{N}^3$ and must select $P \subseteq \mathcal{P}$ such that:

$$\sum_{p \in P} p[0] \geq M$$
$$\sum_{p \in P} p[1] \geq H$$
$$\sum_{p \in P} p[2] \geq W$$

Additionally, we know that $\forall p \in \mathcal{P}$:

**Type A:**
$$p[0] > 0 \land p[1] > 0 \land p[2] = -a$$

or

**Type B:**
$$p[0] = -b \land p[1] = 0 \land p[2] > 0$$

## Solution Approach

Observe that happiness ($p[1]$) will not decrease and can only be increased by potions of type A. We view this as our first objective: take as few potions as possible of type A such that $\sum_{p \in P} p[1] \geq H$. While we could solve this greedily, we know exactly how much wit will decrease given the number of type A potions we take. This allows us to establish a clear ordering of solution quality based on how much magical power was maximized.

Let $P_1^A, P_2^A \subseteq \mathcal{P}^A$ with:
- $\sum_{p \in P_1^A} p[0] > \sum_{p \in P_2^A} p[0]$
- $\sum_{p \in P_1^A} p[1] \geq H$ and $\sum_{p \in P_2^A} p[1] \geq H$
- $|P_1^A| = |P_2^A|$

Then, if $P_2$ is part of an optimal solution, $P_1$ is also part of an optimal solution..

For the "best" subset (call it $S^A$) of a given size that has at least $H$ happiness, we can check if $S^A$ is part of a feasible solution by greedily selecting the best potions of type B and verifying if we can fulfill all constraints. Here, $p_1^B$ is better than $p_2^B$ if $p_1^B[0] \geq p_2^B[0]$, which is intuitive since more wit does not hurt and magical power is reduced by the same amount for any potion.

The algorithm iterates through the number of allowed type A potions and checks for a feasible solution with type B potions. When we find a feasible solution for $|S_A| = i$, we can be certain there is no better solution for any $|S_A'| > i$, as increased wit reduction would require at least as many type B potions to reach the wit threshold.

### Algorithm
```
for i = 1 to |𝒫|:
    find m_i (maximum magical power using i potions with ≥ H happiness)
    greedily select type B potions to exceed wit threshold W without dropping below M
    if possible → finished
    else continue (need more type A potions)
```

We use dynamic programming to find $m_i$ by building the following table:
Let $dp[i][j]$ denote the maximum magical power gained by taking $i$ potions and having at least $y$ happiness.

Additionally we need to avoid reusing potions. For this reason we consider one additional potion in each iteration.
```
// Initialize base case
dp[0][0][0] = 0

// Main DP recurrence
for p ∈ {0, ..., |𝒫| - 1}:
    for i ∈ {1, ..., p}:
        for j ∈ {0, ..., H}:
            // Consider whether including potion p improves our solution
            dp[p][i][j] = max(
                dp[p-1][i][j],                    // Don't take potion p
                𝒫[p][0] + dp[p-1][i-1][j - 𝒫[p][1]]  // Take potion p
            ) 
            // edge cases omitted
```



### Testing Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| Test set 1 | 30 pts | 5.500 s | Correct answer | 0.785s |
| Test set 2 | 30 pts | 5.500 s | Correct answer | 1.111s |
| Test set 3 | 20 pts | 5.500 s | Correct answer | 1.135s |
| Test set 4 | 20 pts | 5.500 s | Correct answer | 1.079s |


# Severus Snape

## Algorithmic Problem Description

We are given a set of potions $\mathcal{P} \subset \mathbb{N}^3$ and must select $P \subseteq \mathcal{P}$ such that

$\Sigma_{p \in P} \ p[0] \geq M$ 

$\Sigma_{p \in P} \ p[1] \geq H$

$\Sigma_{p \in P} \ p[2] \geq W$ 

Additionally we know that:
$\forall p \in \mathcal{P}:$

$p[0] > 0 \ \land \ p[1] > 0 \ \land \ p[2] = -a \quad \quad $  (type A)

or 

$p[0] = -b \ \land \ p[1] = 0 \ \land \ p[2] > 0 \quad \quad $  (type B)



## Solution Appraoch

Observe that no matter the potion, our happiness ($p[1]$) will not decrease and can only be increased by potions of type A. We view this as our first objective: take as little potions as possible of type A such that $\Sigma_{p \in P} \ p[1] \geq H$. We could solve this greedily but because we know exactly by how much wit will decrease given the number of potions of type $A$ we take, we can establish a clear ordering of the goodness of the solution depending on how much our magical power was maximized. 

Let $P_1, P_2 \subseteq \mathcal{P}_A$ with:

- $\Sigma_{p \in P_1} \ p[0] > \Sigma_{p \in P_2} \ p[0]$ 

- $\Sigma_{p \in P_1} \ p[1] \geq H \ \ $ and $ \ \ \Sigma_{p \in P_2} \ p[1] \geq H$

- $|P_1| = |P_2|$

$\implies$

If $P_2$ is part of an optimal solution, then $P_1$ is also part of an optimal solution.

Now if we have the "best" subset, we call it $S_A$$ for a given size that has at least $H$ happiness we can check if $S_B$ is part of a feasable solution by greedily picking the best potions of type $B$ and seeing if we can fulfill all constraints. By best I mean:

$p_1^B$ is better than $p_2^B$ if $p_1^B[0] \geq p_2^B[0]$. Which makes intutitively sense because more Wit does not hurt and the magical power is reduced by the same amount for any potion.


The idea now is to iterate through the number of potions we are allowed to use of type A and check for a feasable solution with potions of type B. Now assuming that we found a feasable solution for $|S_A| = x$ can we be sure that there is not better solution for some $|S_A'| > x$? Yes we can. I am not going to prove it here but it is intuitively clear because the wit is reduced more meaning we need at least as many potions of type B to reach the wit thereshold. 

For our ideas above we can generate the following algorithm:

for i=1 to $|\mathcal{P}|$:
    
    find $m_i$ which denotes the maximum magical power we can get by using $i$ potions and getting at least $H$ happiness (the required amount)

    greedily pick potions of type B and check if we can get above the wit thereshold $W$ without dropping below $M$ threshold.

    if possible -> finished
    else continue as we need to take more potions of type A


The last question that is unanswered is how to get the value $m_i$ which is what we will use dynamic programming for. We build the following table:  

$dp[i][y]$ denoting the maximum amount of magical power that can be gained by taking $i$ potions and having at least $y$ happiness.

$dp[i][0] = argmax_{P^A \subseteq \mathcal{P} \land |P^A| = i} \Sigma_{p \in P^A} \ p[0]$


$dp[i][j] = max_p (p[0] + dp[i-1][j - p[1]])$



### Testing Results

| Test Set | Points | Time Limit | Result | Execution Time |
|----------|---------|------------|---------|----------------|
| Test set 1 | 30 pts | 5.500 s | Correct answer | 0.785s |
| Test set 2 | 30 pts | 5.500 s | Correct answer | 1.111s |
| Test set 3 | 20 pts | 5.500 s | Correct answer | 1.135s |
| Test set 4 | 20 pts | 5.500 s | Correct answer | 1.079s |