# On Her Majesty’s Secret Service

## Problem Description

Given a directed graph $G=(V,E)$ with $|V| \leq 10^3$ vertices and $|E| \leq 5 \cdot 10^3$ edges (both directed and bidirectional), $a \leq 10^2$ agents at starting vertices $\{\alpha_i\}$, and $s \leq 10^2$ target vertices $\{\sigma_j\}$ (shelters) each with capacity $c \leq 2$ and sequential processing time $d$, compute the minimum time needed for all agents to reach and be processed by some shelter. Each edge has a traversal time $t_e$, can be used by multiple agents simultaneously, and shelters process agents one at a time while respecting their capacity limit.

## Solution Appraoch

We first compute the distance from each agent to each shelter using Dijkstras algorithm. We can then use binary search to find the minimal warning time such that each agent gets to a shelter. The main challenge of this task is to determine wether it is possible to save all agents given a waiting time.

To solve this sub problem we employ a Max Flow appraoch. 

- $c=1$: This part is not as tricky. We simply create a graph where each agent is connected to each shelter that (s)he can reach in time. Each agent is connected to the source and each shelter to the sink. If the flow is equal to the number of agents, we know that it is possible to save all agents given the warning time.

- $c=2$: The important realisation to solve this subtask is that in order for two agents to make it safely to the same shelter one agent arrives at the shelter after warning_time - d and the other warning_time - 2d seconds. Thus we can create two nodes for each shelter. For one we create edges from agents that satisfy the first condition and for the other the second condition.