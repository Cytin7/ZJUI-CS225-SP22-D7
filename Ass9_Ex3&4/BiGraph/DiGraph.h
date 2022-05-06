//
// Created by 洪嘉栋 on 2022/5/2.
//
#ifndef BIGRAPH_DIGRAPH_H
#define BIGRAPH_DIGRAPH_H
#define INFINATE = 0x0fffff
#include "queue.h"
// the basic idea is to implement the structure by matrix.
// So the class alist is required.
// Basically, using pointer array to implement the graph...
// Here I directly use the class from Prof. Schewe......
template<class T> class AList
{
public:
    AList(int size = 20);
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void remove(int index);
protected:
    int numitems;
    T *reprarray;
private:
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

template<class T, class K>
class Vertex{
public:
    K value;
    int inDegree;
    int outDegree;
    AList<T> InEdges;
    AList<T> OutEdges;
    bool visited = false;
};
// T can only be int.
template<class T, class K>
class DiGraph {
public:
    DiGraph(int size = 20);
    void InsertVertex(Vertex<T,K>* node);
    // Here we need to modify the array of vertex...
    void DeleteVertex(K value);
    // This function is used to delete vertices via a certain key....
    void InsertDirectEdge(Vertex<T,K>* from, Vertex<T,K>* to, T length = 1);
    // Here we need to modify the BiVertex's InEdge and OutEdge.
    void IDE(int from, int to, T length = 1);
    // Here is the direct insert via index.
    void InsertUndirectEdge(Vertex<T,K>* from, Vertex<T,K>* to, T length = 1);
    // Exectue InsertDirectEdge twice but reverse the order of vertices.
    void DeleteEdge(Vertex<T,K>* from, Vertex<T,K>* to);
    // This function is used to delete the edge via vertex pointer.
    void DE(int from, int to);
    // This function is used to delete the edge via index.
    int getIndex(Vertex<T,K>* node);
    Vertex<T,K>* BFS(K value);
    Vertex<T,K>* DFS(K value, int index = 0);
    bool IsAcyclic();
    void print();
protected:
    int num_vertices;
    int num_edges;
    Vertex<T,K>** vertices;
private:
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

#endif //BIGRAPH_DIGRAPH_H
