# Porj. DiGraph & BiPartiteGraph

### By CS225-D7 Hong Jiadong

## Class DiGraph

The Graph is mainly implemented in the form of an special adjacent matrix.

This class is mainly the authentic Directed Graph with all the required functions.

Including BFS&DFS and insert/delete vertices and edges.

## Class BiPartiteGraph 

The Graph is just a modification of DiGraph.

However, contrary to DiGraph, this edition of BiGraph cannot support weighted edges and perfect matching of weighted, we only consider non-weighted perfect matching.

The function is void flow2match(); note that the function does not check the graph is perfectly matched or not, so the function only work while you are sure it is a perfect matching bipartite graph.