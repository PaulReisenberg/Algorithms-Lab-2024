# Search Snippets

## Problem Description

We are given a set of words $W$ and a mapping $S:W \mapsto \mathcal{P}(\mathbb{N})$ that maps each word to the positions where it appears in a text. We are supposed to find the smallest interval $[a,b]$ such that $\forall w \in W: S(w) \cap [a,b] \neq \emptyset$.

## Solution Appraoch

This problem can be solved using a simple sliding window appraoch and an appropriate choice of data strctures.

## Test Results

I was not able to test the algorithm on all test cases.
