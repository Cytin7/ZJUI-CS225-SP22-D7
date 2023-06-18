//
// Created by 洪嘉栋 on 2022/5/2.
//
#include <iostream>
#include "DiGraph.h"
#include "queue.h"
using namespace std;
// Defination of AList.
template<class T> AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template<class T> T &AList<T>::operator[](int index)
{
    return reprarray[index];
}

template<class T> int AList<T>::getlength(void)
{
    return numitems;
}

template<class T> void AList<T>::setitem(int index, T value)
{
    if ((index >= 0) && (index < numitems))
    {
        reprarray[index] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T AList<T>::getitem(int index)
{
    if ((index >= 0) && (index < numitems))
    {
        return reprarray[index];
    }
    else
    {
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T>
void AList<T>::remove(int index) {
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index < numitems)
    {
        for (int j = index; j < numitems - 1; ++j)
        {
            reprarray[j] = reprarray[j+1];
        }
        numitems--;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template<class T> void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void AList<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}



template<class T, class K>
DiGraph<T,K>::DiGraph(int size) {
    num_vertices = 0;
    num_edges = 0;
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    vertices = new Vertex<T,K>* [size];
    return;
}

template<class T,class K>
void DiGraph<T, K>::InsertVertex(Vertex<T, K>* node) {
    if (num_vertices == maxsize)
        allocate();
    vertices[num_vertices] = node;
    for (int i = 0; i < num_vertices; i++){
        Vertex<T,K>* V = vertices[i];
        V->OutEdges.append(0);
        V->InEdges.append(0);
    }
    num_vertices++;
    for (int i = 0; i < num_vertices; ++i) {
        node->InEdges.append(0);
        node->OutEdges.append(0);
    }
    return;
}

template<class T, class K>
void DiGraph<T,K>::allocate() {
    int newsize = 2 * maxsize;
    Vertex<T,K> **newarray = new Vertex<T,K>* [newsize];
    for (int i = 0; i < num_vertices; ++i)
    {
        newarray[i] = vertices[i];
    }
    delete[] vertices;
    vertices = newarray;
    maxsize = newsize;
    return;
}

template<class T, class K>
void DiGraph<T,K>::deallocate() {
    int newsize = maxsize / 2;
    Vertex<T,K> **newarray = new Vertex<T,K>* [newsize];
    for (int i = 0; i < num_vertices; ++i)
    {
        newarray[i] = vertices[i];
    }
    delete[] vertices;
    vertices = newarray;
    maxsize = newsize;
    return;
}

template<class T, class K>
int DiGraph<T,K>::getIndex(Vertex<T, K>* node) {
    for (int i = 0; i < num_vertices; i++){
        if (vertices[i] == node){
            return i;
        }
    }
    cout << "getIndex Error: There is no such pointer in the Graph." << endl;
    return -1;
}

template<class T, class K>
void DiGraph<T,K>::InsertDirectEdge(Vertex<T, K>* from, Vertex<T, K>* to, T length) {
    // to define the node is in the graph or not.
    int fromIdx = getIndex(from);
    if (fromIdx == -1){
        cout << "InsertEdge Error: The input pointer of the node is not in the Graph." << endl;
        return;
    }
    int toIdx = getIndex(to);
    if (toIdx == -1){
        cout << "InsertEdge Error: The input pointer of the node is not in the Graph." << endl;
        return;
    }
    if (from->OutEdges[toIdx] != 0){
        cout << "InsertEdge Error: The input pointer of the nodes has already have a edge in the Graph." << endl;
        return;
    }
    // Here we should modify the num_edge first...
    num_edges++;
    // then into the two specific nodes add edges.
    from->outDegree++;
    from->OutEdges.setitem(toIdx,length);
    to->inDegree++;
    to->InEdges.setitem(fromIdx,length);
    cout << "InsertEdge successful! the New Edge is from node No."
         << fromIdx+1 << " to node No." << toIdx+1 << "; "
         << "The length is " << length << "." << endl;
    return;
}

template<class T,class K>
void DiGraph<T,K>::IDE(int from, int to, T length) {
    if ((from >= num_vertices || from < 0) || (to >= num_vertices || to < 0)){
        cout << "indexError: the insertEdge is out of range." << endl;
        return;
    }else{
        if (vertices[from]->OutEdges[to] != 0){
            cout << "InsertEdge Error: The input pointer of the nodes has already have a edge in the Graph." << endl;
            return;
        }
        // Here we should modify the num_edge first...
        num_edges++;
        // then into the two specific nodes add edges.
        vertices[from]->outDegree++;
        vertices[from]->OutEdges.setitem(to,length);
        vertices[to]->inDegree++;
        vertices[to]->InEdges.setitem(from,length);
        cout << "InsertEdge successful! the New Edge is from node No."
             << from+1 << " to node No." << to+1 << "; "
             << "The length is " << length << "." << endl;
        return;
    }
}

template<class T,class K>
void DiGraph<T,K>::InsertUndirectEdge(Vertex<T, K> *from, Vertex<T, K> *to, T length) {
    InsertDirectEdge(from,to,length);
    InsertDirectEdge(to,from,length);
    return;
}

template<class T,class K>
Vertex<T, K> *DiGraph<T, K>::BFS(K value) {
    if (num_vertices == 0){
        cout << "BFSError: No vertex in the graph... Thus no such node has the value input..." <<endl;
        return NULL;
    }else{
        Vertex<T,K>* V;
        queue<int>* fifo = new queue<int>;
        // remember to set the visited status back to false....
        // the queue stores the current node's index in the vertices array.
        for (int j = 0; j < num_vertices; j++) {
            // this case is to avoid the disconnected graph.
            // if one set graph is completed...
            V = vertices[j];
            if (!V->visited){
                if (V->value == value){
                    // output, but reset the status of the visit status...
                    for (int k = 0; k < num_vertices; k++){
                        Vertex<T,K>* U = vertices[k];
                        U->visited = false;
                    }
                    cout << "Complete the BFS, finding that the input value has a index of "
                         << j << "." << endl;
                    return vertices[j];
                }
                vertices[j]->visited = true;
                fifo->enqueue(j);
                while (!fifo->isEmpty()) {
                    V = vertices[fifo->queue<T>::dequeue()];
                    for (int i = 0; i < num_vertices; i++) {
                        // loop through every vertex
                        // that is the Edge-out vertex of the current node.
                        if (V->OutEdges[i] != 0) {
                            Vertex<T,K>* W = vertices[i];
                            if (!W->visited) {
                                if (W->value == value){
                                    // output, but reset the status of the visit status...
                                    for (int k = 0; k < num_vertices; k++){
                                        Vertex<T,K>* U = vertices[k];
                                        U->visited = false;
                                    }
                                    cout << "Complete the BFS, finding that the input value has a index of "
                                         << i << "." << endl;
                                    return W;
                                }
                                W->visited = true;
                                fifo->enqueue(i);
                            }
                        }
                    }
                }
            }
        }
        // output, but reset the status of the visit status...
        for (int k = 0; k < num_vertices; k++){
            Vertex<T,K>* U = vertices[k];
            U->visited = false;
        }
        cout << "Complete the BFS, No such vertex have the value input." << endl;
        return NULL;
    }
}

template<class T, class K>
Vertex<T,K> *DiGraph<T,K>::DFS(K value, int index) {
    if (index >= num_vertices){
        for (int k = 0; k < num_vertices; k++){
            Vertex<T,K>* U = vertices[k];
            U->visited = false;
        }
        cout << "DFSError: searching value not found." << endl;
        return NULL;
    }
    vertices[index]->visited = true;
    Vertex<T,K>* V = vertices[index];
    if (V->value == value){
        // output, but reset the status of the visit status...
        for (int k = 0; k < num_vertices; k++){
            Vertex<T,K>* U = vertices[k];
            U->visited = false;
        }
        cout << "Complete the DFS, finding that the input value has a index of "
             << index << "." << endl;
        return V;
    }
    for (int i = 0; i < num_vertices; i++){
        if (V->OutEdges[i] != 0){
            Vertex<T,K>* W = vertices[i];
            if (W->value == value){
                // output, but reset the status of the visit status...
                for (int k = 0; k < num_vertices; k++){
                    Vertex<T,K>* U = vertices[k];
                    U->visited = false;
                }
                cout << "Complete the DFS, finding that the input value has a index of "
                     << i << "." << endl;
                return W;
            }
            if (!W->visited){
                DFS(value,i);
            }
        }
    }
    index++;
    return DFS(value,index);
}

template<class T, class K>
bool DiGraph<T, K>::IsAcyclic() {
    // by using TopSort we can define whether DAG...
    AList<int> Indegree;
    queue<int> fifo;
    for (int i = 0; i < num_vertices; i++){
        Indegree.append(vertices[i]->inDegree);
    }
    for (int i = 0; i < num_vertices; i++){
        if (Indegree.getitem(i) == 0){
            fifo.enqueue(i);
        }
    }
    int cnt = 0;
    while (!fifo.isEmpty()){
        int temp = fifo.queue<int>::dequeue();
        cnt++;
        for (int j = 0; j < num_vertices; j++){
            if (vertices[temp]->OutEdges[j] != 0){
                Indegree.setitem(j,Indegree.getitem(j)-1);
                if(Indegree.getitem(j) == 0){
                    fifo.enqueue(j);
                }
            }
        }
    }
    for (int k = 0; k < num_vertices; k++){
        Vertex<T,K>* U = vertices[k];
        U->visited = false;
    }
    if (cnt != num_vertices){
        cout << "there is a cycle in this map." << endl;
        return false;
    }else{
        return true;
    }
}

template<class T,class K>
void DiGraph<T, K>::print() {
    for (int i = 0; i < num_vertices; i++){
        Vertex<T,K>* V = vertices[i];
        cout << "the No." << i+1 << " element is " << V->value << " ";
        for (int j = 0; j < num_vertices; j++){
            cout << "(" << V->InEdges[j] << " , "<< V->OutEdges[j] << ") ";
        }
        cout<< "the in degree is " << vertices[i]->inDegree << ", "
            << "the out degree is " << vertices[i]->outDegree <<"." <<endl;
    }
}

template<class T, class K>
void DiGraph<T, K>::DeleteEdge(Vertex<T, K> *from, Vertex<T, K> *to) {
    // to define the node is in the graph or not.
    int fromIdx = getIndex(from);
    if (fromIdx == -1){
        cout << "deleteEdge Error: The input pointer of the node is not in the Graph." << endl;
        return;
    }
    int toIdx = getIndex(to);
    if (toIdx == -1){
        cout << "deleteEdge Error: The input pointer of the node is not in the Graph." << endl;
        return;
    }
    if (from->OutEdges[toIdx] == 0){
        cout << "deleteEdge Error: The input pointer of the nodes has no edge in the Graph." << endl;
        return;
    }
    // Here we should modify the num_edge first...
    num_edges--;
    // then into the two specific nodes add edges.
    from->outDegree--;
    from->OutEdges.setitem(toIdx,0);
    to->inDegree--;
    to->InEdges.setitem(fromIdx,0);
    cout << "deleteEdge successful! the old Edge is from node No."
         << fromIdx+1 << " to node No." << toIdx+1 << "." << endl;
    return;
}

template<class T, class K>
void DiGraph<T, K>::DE(int from, int to) {
    if ((from >= num_vertices || from < 0) || (to >= num_vertices || to < 0)){
        cout << "indexError: the DeleteEdge is out of range." << endl;
        return;
    }else{
        if (vertices[from]->OutEdges[to] == 0){
            cout << "DeleteEdge Error: The input pointer of the nodes has no edge in the Graph." << endl;
            return;
        }
        // Here we should modify the num_edge first...
        num_edges--;
        // then into the two specific nodes add edges.
        vertices[from]->outDegree--;
        vertices[from]->OutEdges.setitem(to,0);
        vertices[to]->inDegree--;
        vertices[to]->InEdges.setitem(from,0);
        cout << "deleteEdge successful! the old Edge is from node No."
             << from+1 << " to node No." << to+1 << "." << endl;
        return;
    }
}

template<class T, class K>
void DiGraph<T,K>::DeleteVertex(K value) {
    Vertex<T,K>* ptr = BFS(value);
    if (ptr == NULL){
        cout << "DeleteVertexError: Input value not exist." << endl;
        return;
    }
    int index = getIndex(ptr);
    if ((num_vertices == maxsize / 4) && (maxsize > minsize))
        deallocate();
    vertices[num_vertices] = ptr;
    for (int i = 0; i < num_vertices; i++){
        if (vertices[index]->OutEdges[i] != 0){
            DE(index,i);
        }
        if (vertices[index]->InEdges[i] != 0){
            DE(i,index);
        }
    }
    for (int i = index; i < num_vertices - 1; i++){
        vertices[i] = vertices[i+1];
    }
    num_vertices--;
    for (int i = 0; i < num_vertices; i++){
        Vertex<T,K>* V = vertices[i];
        V->OutEdges.remove(index);
        V->InEdges.remove(index);
    }
    delete ptr;
    return;
}
