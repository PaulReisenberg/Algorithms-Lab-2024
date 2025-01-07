# Canteen

## Problem Description

Given $n$ days where each day $i$ has production capacity $a_i$, cost per menu $c_i$, student demand $s_i$, and fixed menu price $p_i$. Between consecutive days, $v_i$ menus can be stored at cooling cost $e_i$ per menu. The task is to: (1) determine if all student demand can be met using production and storage constraints, and (2) maximize profit (revenue minus costs) while serving maximum possible students. Constraints: $1 \leq n \leq 1000$, all other parameters $\leq 300$ except costs/prices $\leq 20$.

## Solution Appraoch

Solution uses min-cost max-flow on a graph constructed as follows:
- Source connected to each day's production node with capacity $a_i$ and cost $c_i$
- Day nodes connected to sink with capacity $s_i$ (student demand) and cost $max\_cost - p_i$ 
- Adjacent days connected with capacity $v_i$ and cost $e_i$ for storage

Flow represents meals served, cost includes production/storage minus revenue (using $max\_cost$ offset). Push-relabel finds max flow, then successive shortest paths minimizes cost. Output "possible" if flow equals total demand.

## Test Results

| Test Set | Points | Time Limit | Result | Runtime |
|----------|---------|------------|---------|----------|
| 1 | 30 pts | 2 s | ✓ Correct answer | 1.411s |
| 2 | 50 pts | 2 s | ✓ Correct answer | 0.171s |
| 3 | 20 pts | 2 s | ✓ Correct answer | 1.752s |
