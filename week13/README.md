# Fighting Pits of Meereen

## Algorithmic Problem Description

We have $n$ fighters in a queue that are of $k$ different types. Each fighter can be sent to the north or the south enterence. The crowd can remember at most $m$ fighters. The excitement of a round can be calculated as:

$$
1000 \cdot \text{distinct fighters sent though enterence in last m rounds} - 2^{|p-q|} 
$$

where p and q denote the total number of fighters sent though the 2 gates.

## Solution Approach

