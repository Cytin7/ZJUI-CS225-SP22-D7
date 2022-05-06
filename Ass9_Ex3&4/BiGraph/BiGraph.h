//
// Created by 洪嘉栋 on 2022/5/2.
//
#ifndef BIGRAPH_BIGRAPH_H
#define BIGRAPH_BIGRAPH_H
#include <iostream>
#include "queue.h"
#include "DiGraph.h"

typedef bool gender;

template<class T, class K>
class BiVertex : public Vertex<T,K>{
public:
    gender type;
};

template<class T, class K>
class BiPartiteGraph{
public:
    BiPartiteGraph(int size = 20);
    void InsertVertex(BiVertex<T,K>* node);
    // Here we need to modify the array of vertex...
    void DeleteVertex(K value);
    // This function is used to delete vertices via a certain key....
    void InsertDirectEdge(BiVertex<T,K>* from, BiVertex<T,K>* to, T length = 1);
    // Here we need to modify the BiVertex's InEdge and OutEdge.
    void IDE(int from, int to, T length = 1);
    // Here is the direct insert via index.
    void InsertUndirectEdge(BiVertex<T,K>* from, BiVertex<T,K>* to, T length = 1);
    // Exectue InsertDirectEdge twice but reverse the order of vertices.
    void DeleteEdge(BiVertex<T,K>* from, BiVertex<T,K>* to);
    void DE(int from, int to);
    int getIndex(BiVertex<T,K>* node);
    BiVertex<T,K>* BFS(K value);
    BiVertex<T,K>* DFS(K value, int index = 0);
    bool IsAcyclic();
    void print();
    // following function is to compute the largest matching.
    // and check whether it is BiPartite Graph.
    // and also to figure out whether perfect matching is exist or not.
    void flow2match();
protected:
    int num_vertices;
    int num_edges;
    BiVertex<T,K>** vertices;
private:
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

#endif //BIGRAPH_BIGRAPH_H
