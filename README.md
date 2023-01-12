# Vector-Similarity-Search-and-Clustering-Algorithms

## Vector Similarity Search

Implementation of the Locality Sensitive Hashing (LSH) algorithm for vectors on d-dimensional space based on the Manhattan metric (L1)

Implementation of the Random Projections to HyperCube algorithm based on L1

We use input images from the MNIST dataset

## Clustering

Implementation of algorithms for vector clustering
For the initialization step, the k-Means++ technique is used
For the update step, we compute the median vector
For the assignment step we either use 
*the Lloyd's algorithm
*Reverse assignment using LSH range search
*Reverse assignment using Hypercube range search
