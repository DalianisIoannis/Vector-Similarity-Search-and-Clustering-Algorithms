# Vector-Similarity-Search-and-Clustering-Algorithms

## Vector Similarity Search

Implementation of the Locality Sensitive Hashing (LSH) algorithm for vectors on d-dimensional space based on the Manhattan metric (L1)

Implementation of the Random Projections to HyperCube algorithm based on L1

We use input images from the MNIST dataset

Both algorithms aim to find similar vectors approximately but with high probability

Receiving as input a vector q and integers N, R, the program approximately computes
- The nearest neighbor of q
- The N nearest neighbors of q
- All vectors within range R from q (range search)


## Clustering

Implementation of algorithms for vector clustering
For the initialization step, the k-Means++ technique is used
For the update step, we compute the median vector
For the assignment step we either use 

- The Lloyd's algorithm
- Reverse assignment using LSH range search
- Reverse assignment using Hypercube range search
