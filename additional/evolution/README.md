# Evolution

## Problem Description

We are given the "tree of life". Each species has at most one immediate ancestor, but one species can have many immediate ofspring. We are given $q$ queries in the form of ($s$, $b$) to which we have to print out the oldest ancestor of  $s$ that is not older than $b$.

## Solution Appraoch

Because we can have as many queries as species in the tree of life, it makes sense to use binary search here to not traverse the tree in $\mathcal{O}(n)$ for each new query but only once at the beginning, creating a data structure that allows us to do binary search for each query. To do this, we create a new list for every leaf in the tree. This list contains all species, from the leaf to the oldest ancestor. Every species that is not a leaf is in of some list beginning at a leaf, and we only need to store the index of that list and the position of the species in that list. Based on these lists, we can simply perform a binary search to find the oldest ancestor that is not older than the specified age.


