# Clues

## Algorithmic Problem Description

We are given a set of $n$ stations $s_0, .., s_{n-1}$ positioned in the $\mathbb{R}^2$ plane. Additionally, we are given $m$ clues, each defined by a starting position $a_i$ and end position $b_i$. 

The following definitions are given:
- A network without interferences corresponds to a map: $f: S \rightarrow \{0,1\}$ such that $f(u) \neq f(v)$ for all u, v with $||u-v|| \leq r$ a.k.a. the graph we get by connecting points with a distance $\leq r$ is bipartite.

- A clue can be $\textit{routed}$ from $a_i$ to $b_i$, if there exists a network without interferences on $S$ and there exist $k \in \mathbb{N}$ and a sequence $t_0,\ldots,t_k$, such that

    1. $t_0 = a_i$, $t_k = b_i$, and $t_j \in S$, for $j \in \{1,\ldots,k-1\}$;

    2. $\|t_j - t_{j-1}\| \leq r$, for all $j \in \{1,\ldots,k\}$;

    3. If $t_j \neq b_i$ (and, thus, $t_{k-1} \neq a_i$), then $t_j$ is the (unique) client from $S$ that is closest to $a_i$ and $t_{k-1}$ is the (unique) client from $S$ that is closest to $b_i$.

For each clue determine if the network has interferences and if the clue can be routed.


## Solution Approach

### Checking Bipariteness

This step is obvious as the network of stations has to be bipartite. We donote $G_{\leq r}$ as the graph we get when we only keep the edges that are $\leq r$ and we deonte $D^G$ as the Delauney Triangulation of $G$. Helpful to us is the following relation:
$$
(1) \ \ \ G_{\leq r} \text{ is bipartite} \Rightarrow  D^G_{\leq r} \text{ is bipartite}
$$
One does not have to be convinced that this implication holds. The better question is why the following holds:


$(2) \ \ \ $ Let $G_{\leq r}$ be bipartite and let $A$ and $B$ be a set of vertices that form a bipartition of $D^{G}_{\leq r}$. It follows that $A$ and $B$ also form a bipartition of $G_{\leq r}$.

Proof Sketch:
Let $A$, $B$ a bipartition of $D^G_{\leq r}$.

Assume there be an edge $(u,v) \in G_{\leq r}$ with $u,v \in A$ that is not in $D^G_{\leq r}$.
- We know that there have to exist two vertives $x, y \in B$ with $(u,x), (v,y) \in D_G$ and  $||u-x|| \leq r$ and $||v-y|| \leq r$. This is because the Delaunay Triangulation contains the nearest neighbor graph and because $u$ and $v$ are not nearest neighbors $u$ and $v$ must have nearest neighbors $x$ and $y$ that are even closer to each other than $u$ and $v$ are to themselves. Because $D^G_{\leq r}$ is bipartite $x,y \in B$ must hold.
- There has to be a path of $even$ length from $x$ to $y$ in $D^G_{\leq r}$. This is because 
    
    1. The Delaunay Triangulation contains the Minimum Spanning Tree. Therefore, there has to be a path from $x$ to $y$ in $D^G$.
    2. There has to be a path from $x$ to $y$ where the length of each edge is $\leq r$ because if not you could obtain a cheaper MST by including $(u,v)$.
    3. This path needs to be of even length because the graph $D^G_{\leq r}$ is bipartite.

This means that there would be a circle in G of uneven length $(u,v,y,...,x, u)$ making the graph not bipartite. Thus, $(u,v)$ can't exist and $A$, $B$ forms a bipartition on $G$.

### Implementation

We can implement the bipartite check using BFS on $D_{\leq r}^G$ by 2-coloring the vertices. Additionally, we record the connected component for each vertex. If the 2-coloring on $D_{\leq r}^G$ succeed, we have a candidate coloring for $G_{\leq r}$ and we know because of (2) that $G_{\leq r}$ is bipartite iff. this candidate bipartites $G_{\leq r}$. We can check the candidate by building the Delauney Triangulation of each color class and checking if the shortest edge is still $\geq r$. If so we know that $G_{\leq r}$ must be bipartite.

Now we only need to check if Watson and Holmes can communicate. For each clue we first check if there can be a direct communication, i.e. $||a_i - b_i|| \leq r$. If not, we check if the nearest stations to $a_i$ and $b_i$ are within reach and if so is they are in the same connected component.  

## Learnings
- for(auto v = t.finite_vertices_begin(); v $\textbf{<}$ t.finite_vertices_end(); v++) is wrong it must be !=
- Watch out which Kernel you are using! It might cost you a lot of time...
- Use double instead of long for distance measurement

## Test Results

| Test Set | Points | Time Limit | Status | Time |
|----------|---------|------------|---------|------|
| 1 | 20 pts | 2 s | Correct answer | 0.064s |
| 2 | 30 pts | 2 s | Correct answer | 0.658s |
| 3 | 30 pts | 2 s | Correct answer | 1.048s |
| 4 | 20 pts | 2 s | Correct answer | 1.23s |

**Total Score:** 100 points
