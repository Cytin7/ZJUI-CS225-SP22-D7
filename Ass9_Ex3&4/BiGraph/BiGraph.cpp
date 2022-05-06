//
// Created by 洪嘉栋 on 2022/5/2.
//
#include <iostream>
#include "BiGraph.h"
#include "queue.h"
using namespace std;

template<class T,class K>
BiPartiteGraph<T,K>::BiPartiteGraph(int size){
    num_vertices = 0;
    num_edges = 0;
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    vertices = new BiVertex<T,K>* [size];
    return;
}

template<class T, class K>
void BiPartiteGraph<T, K>::allocate(){
    int newsize = 2 * maxsize;
    BiVertex<T,K> **newarray = new BiVertex<T,K>* [newsize];
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
void BiPartiteGraph<T, K>::deallocate(){
    int newsize = maxsize / 2;
    BiVertex<T,K> **newarray = new BiVertex<T,K>* [newsize];
    for (int i = 0; i < num_vertices; ++i)
    {
        newarray[i] = vertices[i];
    }
    delete[] vertices;
    vertices = newarray;
    maxsize = newsize;
    return;
}

template<class T,  class K>
void BiPartiteGraph<T, K>::InsertVertex(BiVertex<T, K> *node) {
    if (num_vertices == maxsize)
        allocate();
    vertices[num_vertices] = node;
    for (int i = 0; i < num_vertices; i++){
        BiVertex<T,K>* V = vertices[i];
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
int BiPartiteGraph<T, K>::getIndex(BiVertex<T, K> *node) {
    for (int i = 0; i < num_vertices; i++){
        if (vertices[i] == node){
            return i;
        }
    }
    cout << "getIndex Error: There is no such pointer in the Graph." << endl;
    return -1;
}

template<class T,class K>
void BiPartiteGraph<T, K>::DeleteVertex(K value) {
    BiVertex<T,K>* ptr = BFS(value);
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
        BiVertex<T,K>* V = vertices[i];
        V->OutEdges.remove(index);
        V->InEdges.remove(index);
    }
    delete ptr;
    return;
}

template<class T, class K>
void BiPartiteGraph<T, K>::InsertDirectEdge(BiVertex<T, K> *from, BiVertex<T, K> *to, T length) {
    // modify to ensure the graph is BiGraph...
    if (from->type == to->type){
        cout << "InsertEdgeError: the insertion is btw the same type." << endl;
        return;
    }
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

template<class T, class K>
void BiPartiteGraph<T, K>::IDE(int from, int to, T length) {
    if ((from >= num_vertices || from < 0) || (to >= num_vertices || to < 0)){
        cout << "indexError: the insertEdge is out of range." << endl;
        return;
    }else{
        if (vertices[from]->type == vertices[to]->type){
            cout << "InsertEdgeError: the insertion is btw the same type." << endl;
            return;
        }
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

template<class T, class K>
void BiPartiteGraph<T, K>::InsertUndirectEdge(BiVertex<T, K> *from, BiVertex<T, K> *to, T length) {
    InsertDirectEdge(from,to,length);
    InsertDirectEdge(to,from,length);
    return;
}

template<class T, class K>
void BiPartiteGraph<T, K>::DeleteEdge(BiVertex<T, K> *from, BiVertex<T, K> *to) {
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
void BiPartiteGraph<T, K>::DE(int from, int to) {
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
BiVertex<T, K> *BiPartiteGraph<T, K>::BFS(K value) {
    if (num_vertices == 0){
        cout << "BFSError: No vertex in the graph... Thus no such node has the value input..." <<endl;
        return NULL;
    }else{
        BiVertex<T,K>* V;
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
                        BiVertex<T,K>* U = vertices[k];
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
                            BiVertex<T,K>* W = vertices[i];
                            if (!W->visited) {
                                if (W->value == value){
                                    // output, but reset the status of the visit status...
                                    for (int k = 0; k < num_vertices; k++){
                                        BiVertex<T,K>* U = vertices[k];
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
            BiVertex<T,K>* U = vertices[k];
            U->visited = false;
        }
        cout << "Complete the BFS, No such vertex have the value input." << endl;
        return NULL;
    }
}

template<class T,class K>
BiVertex<T, K> *BiPartiteGraph<T, K>::DFS(K value, int index) {
    if (index >= num_vertices){
        for (int k = 0; k < num_vertices; k++){
            BiVertex<T,K>* U = vertices[k];
            U->visited = false;
        }
        cout << "DFSError: searching value not found." << endl;
        return NULL;
    }
    vertices[index]->visited = true;
    BiVertex<T,K>* V = vertices[index];
    if (V->value == value){
        // output, but reset the status of the visit status...
        for (int k = 0; k < num_vertices; k++){
            BiVertex<T,K>* U = vertices[k];
            U->visited = false;
        }
        cout << "Complete the DFS, finding that the input value has a index of "
             << index << "." << endl;
        return V;
    }
    for (int i = 0; i < num_vertices; i++){
        if (V->OutEdges[i] != 0){
            BiVertex<T,K>* W = vertices[i];
            if (W->value == value){
                // output, but reset the status of the visit status...
                for (int k = 0; k < num_vertices; k++){
                    BiVertex<T,K>* U = vertices[k];
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
bool BiPartiteGraph<T, K>::IsAcyclic() {
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
        BiVertex<T,K>* U = vertices[k];
        U->visited = false;
    }
    if (cnt != num_vertices){
        cout << "There is a cycle in this map." << endl;
        return false;
    }else{
        cout << "The graph is acyclic."<<endl;
        return true;
    }
}

template<class T,class K>
void BiPartiteGraph<T, K>::print() {
    for (int i = 0; i < num_vertices; i++){
        BiVertex<T,K>* V = vertices[i];
        cout << "the No." << i+1 << " element is " << V->value << " ";
        for (int j = 0; j < num_vertices; j++){
            cout << "(" << V->InEdges[j] << " , "<< V->OutEdges[j] << ") ";
        }
        cout<< "the in degree is " << vertices[i]->inDegree << ", "
            << "the out degree is " << vertices[i]->outDegree <<"." <<endl;
    }
}


// Here above we basically implement basic operation for Ex4 (i)
// the following code is to find the perfect matching of the graph.


template<class T, class K>
void BiPartiteGraph<T, K>::flow2match() {
    // implement the maxmium flow algorithm.
    BiVertex<T,K>* Source = new BiVertex<T,K>;
    Source->type = false;
    BiVertex<T,K>* Sink = new BiVertex<T,K>;
    Sink->type = true;
    BiPartiteGraph<T,K>* RGraph = new BiPartiteGraph<T,K>;
    for (int i = 0; i < num_vertices; i++){
        BiVertex<T,K>* temp = new BiVertex<T,K>;
        temp->type = vertices[i]->type;
        temp->value = vertices[i]->value;
        RGraph->InsertVertex(temp);
    }
    // connect the source and the sink,
    // construct the DiGraph of the flow.
    RGraph->InsertVertex(Sink);
    RGraph->InsertVertex(Source);
    for (int i = 0; i < num_vertices; i++){
        if (RGraph->vertices[i]->type == true){
            RGraph->InsertDirectEdge(Source, RGraph->vertices[i]);
            for (int j = 0; j < num_vertices; j++){
                if (vertices[i]->OutEdges[j] && vertices[i]->InEdges[j]){
                    RGraph->IDE(i,j);
                }
            }
        }else{
            RGraph->InsertDirectEdge(RGraph->vertices[i],Sink);
        }
    }
    RGraph->print();
    // Begin to cycle loops.
    // used for Dijkstra Algorithm. And defineing path to go.
    T* dist = new T[num_vertices+2];
    int* path = new int[num_vertices+2];
    while(true){
        // reset all the beginning nodes.
        for (int i = 0; i < num_vertices + 2; i++){
            dist[i] = (0x1fffff);
            path[i] = -1;
        }
        dist[num_vertices] = 0;
        path[num_vertices] = -1;
        int mini = num_vertices;
        int cnt = 1;
        while(1){
            // traversal to find the minimum.
            // first min is the source...
            for (int i = 0; i < num_vertices + 2; i++){
                if (RGraph->vertices[i]->visited == false)
                    mini = i;
                break;
            }
            for (int i = 0; i < num_vertices + 2; i++){
                if (RGraph->vertices[i]->visited == false && dist[i] <= dist[mini]){
                    mini = i;
                    cnt++;
                }
            }
            if (cnt == 0)
                break;
            cnt = 0;
            RGraph->vertices[mini]->visited = true;
            for (int i = 0; i < num_vertices + 2; i++){
                if (RGraph->vertices[mini]->InEdges[i] && RGraph->vertices[i]->visited == false){
                    if (dist[mini] + RGraph->vertices[mini]->InEdges[i] < dist[i]){
                        dist[i] = dist[mini] + RGraph->vertices[mini]->InEdges[i];
                        path[i] = mini;
                    }
                }
            }
        }
        for (int i = 0; i < num_vertices + 2; i++){
            RGraph->vertices[i]->visited = false;
        }
        //
        // testing dijkstra...
        for (int i = 0; i < num_vertices+2; i++){
            cout << RGraph->vertices[i]->value << ": " << path[i] << ", " << dist[i] << endl;
        }
        cout << endl;
        //
        cout << dist[num_vertices+1]<< endl;
        if (dist[num_vertices+1] == (0x1fffff))
            break;
        else{
            // here we should implement the FF algorithm.
            int current = num_vertices + 1;
            cout << path[current] << ", " << current << endl;
            while(path[current] != -1){
                cout << path[current] << endl;
                RGraph->DE(current,path[current]);
                RGraph->IDE(path[current],current);
                current = path[current];
            }
        }
        RGraph->print();
    }
    RGraph->print();
    // output the whole matching graph.
    cout << endl;
    cout << "Successfully match!" << endl;
    for (int i = 0; i < num_vertices; i++){
        BiVertex<T,K>* V = vertices[i];
        BiVertex<T,K>* W = RGraph->vertices[i];
        if (V->type == true){
            for (int j = 0; j < num_vertices; j++) {
                if ((V->OutEdges[j] - W->OutEdges[j])!=0) {
                    cout << "the No." << i+1 << " and No." << j+1 << " is a BiPartite in the Graph." << endl;
                }
            }
        }
    }
    RGraph->print();
    print();
    for (int i = 0; i < num_vertices+2; i++){
        delete RGraph->vertices[i];
    }
    delete RGraph;
    delete[] path;
    delete[] dist;
    return;
}