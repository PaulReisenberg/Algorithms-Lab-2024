# Important Bridges

## Problem Description

In my approach to the Important Bridges problem, I leverage the concept of biconnected components using Boost's Graph Library. I create an undirected graph from the input and apply the biconnected_components algorithm, which is the core of my solution. This algorithm efficiently identifies all biconnected components in the graph. I use a property map to store component information for each edge. After running the algorithm, I count the size of each component, recognizing that any edge belonging to a component of size 1 is a bridge, as its removal would disconnect the graph. I collect these bridges, ensuring the smaller island number is listed first for each one. Lastly, I sort the list of bridges lexicographically to meet the problem's output requirements. This method allows me to identify all critical bridges without individually testing each bridge, effectively handling the given constraints on the number of islands and bridges.


### Test Scores

| Test Set   | Points | Time Limit | Result         | Execution Time |
|------------|--------|------------|----------------|----------------|
| Test set 1 | 40 pts | 2 s        | Correct answer | 0.005s         |
| Test set 2 | 40 pts | 2 s        | Correct answer | 0.384s         |
| Test set 3 | 20 pts | 2 s        | Correct answer | 0.000s         |