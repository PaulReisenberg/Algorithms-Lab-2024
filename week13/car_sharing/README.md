# Car Sharing

## Problem Description

We are given a set $S \leq 10$ rental stations. Each station has some number $l_i \leq 100$ cars that are initially positioned at that station. Furthermore, we get $N \leq 10^4$ rental requests. Each request contains a start station and end station, an depature time and an arrival time $\leq 10^5$ and a price that this customer is willing to pay for the trip. We now have to select a set of booking requests that are feasable and maximise our profit. The cars do not have to return to their starting station.

## Conceptual Solution

We can model this problem as a $\textit{Max Flow Min Cost}$ problem. We construct the graph in such a way that each station / time combination gets represented by one node in the graph. We add edges from the $source$ to each $(s, 0)$ and edges from $(s, 10^5)$ to the $sink$ for each $s \in S$. The capacities from the $source$ correspond to the number of initial vehicles parked at that station. For each $s \in S$ and $t \in [1, 10^5]$ we add the edges $(s, t-1)$ to $(s,t)$ with infinite capacity and no cost, making it possible for vehicles to be parket at that station.

To generate money, we can rent the cars to customers. For each request we can add an edge from (start station, departure time) to (end station, arrival time) with capacity 1 and cost of the negative price that the customer is willing to pay. Solving the $\textit{Max Flow Min Cost}$ problem on this graph will yield the negative solution. However, it is very slow ....

## Optimizations

### Remove Unnecessary Edges

We can simple remove the edges between the same stations at different points in time if no request exists that either arrives or departs during this time frame. Building the graph is a bit tricky, as we do not know the number of nodes in the beginning. I solved it by storing the indices of station / time combinations I need and the edges that I need in a tuple vector before constructing the graph in the final step.

### Avoid Negative Edges

To avoid negative edges we can add 100 times the time difference of two nodes to the edge cost. This ensures that each car will encur $100 * 10^5$ of cost to reach the sink reduced by the money this car collected by being rented out to customers. We need the 100 to ensure that the edge costs stay positive in all cases.

## Test Results


| Test Set | Points | Time Limit | Result | Actual Time |
|-----------|---------|------------|----------|-------------|
| 1 | 20 | 5s | ✓ | 0.081s |
| 2 | 20 | 5s | ✓ | 0.025s |
| 3 | 20 | 5s | ✓ | 0.18s |
| 4 | 20 | 5s | ✓ | 0.884s |
| 5 | 20 | 5s | ✓ | 1.75s |


