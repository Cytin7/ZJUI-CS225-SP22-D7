#include <iostream>
using namespace std;
#include "BiGraph.h"
#include "BiGraph.cpp"
#include "DiGraph.h"
#include "DiGraph.cpp"
#include "queue.h"

int main() {
    /*
    // testing the insertion of the vertices.
    DiGraph<int,char> graph;
    BiVertex<int,char>* a = new BiVertex<int,char>;
    a->value = 'a';
    graph.InsertVertex(a);
    BiVertex<int,char>* b = new BiVertex<int,char>;
    b->value = 'b';
    graph.InsertVertex(b);
    BiVertex<int,char>* c = new BiVertex<int,char>;
    c->value = 'c';
    graph.InsertVertex(c);
    BiVertex<int,char>* d = new BiVertex<int,char>;
    d->value = 'd';
    graph.InsertVertex(d);
    BiVertex<int,char>* e = new BiVertex<int,char>;
    e->value = 'e';
    graph.InsertVertex(e);
    BiVertex<int,char>* f = new BiVertex<int,char>;
    f->value = 'f';
    graph.InsertVertex(f);
    BiVertex<int,char>* g = new BiVertex<int,char>;
    g->value = 'g';
    graph.InsertVertex(g);
    BiVertex<int,char>* h = new BiVertex<int,char>;
    h->value = 'h';
    graph.InsertVertex(h);
    graph.InsertDirectEdge(a,b,1);
    graph.print();
    graph.IDE(0,1,1);
    graph.print();
    graph.IDE(7,6,1);
    graph.print();
    graph.InsertDirectEdge(h,g,1);
    graph.print();
    graph.IDE(8,7,1);
    // graph.IDE(1,0,1);
    graph.IDE(5,6,1);
    graph.print();
    // testing for BFS & DFS
    if (graph.DiGraph<int,char>::IsAcyclic()){
        cout << "is acyclical." << endl;
    }else{
        cout << "nope." << endl;
    }
    graph.IDE(1,0,1);
    if (graph.DiGraph<int,char>::IsAcyclic()){
        cout << "is acyclical." << endl;
    }else{
        cout << "nope." << endl;
    }
    graph.DFS('g');
    graph.DFS('l');
    graph.print();
    graph.BFS('d');
    graph.print();
    cout << "not" << endl;
    graph.BFS('j');
    graph.DE(0,1);
    graph.print();
    graph.InsertDirectEdge(a,b,1);
    graph.DeleteEdge(a,b);
    graph.print();
    if (graph.DiGraph<int,char>::IsAcyclic()){
        cout << "is acyclical." << endl;
    }else{
        cout << "nope." << endl;
    }
    graph.DeleteVertex('a');
    graph.print();
    */

    BiPartiteGraph<int,char> graph;
    BiVertex<int,char>* a = new BiVertex<int,char>;
    a->type = true;
    a->value = 'a';
    graph.InsertVertex(a);
    BiVertex<int,char>* b = new BiVertex<int,char>;
    b->type = false;
    b->value = 'b';
    graph.InsertVertex(b);
    BiVertex<int,char>* c = new BiVertex<int,char>;
    c->type = true;
    c->value = 'c';
    graph.InsertVertex(c);
    BiVertex<int,char>* d = new BiVertex<int,char>;
    d->type = false;
    d->value = 'd';
    graph.InsertVertex(d);
    BiVertex<int,char>* e = new BiVertex<int,char>;
    e->type = true;
    e->value = 'e';
    graph.InsertVertex(e);
    BiVertex<int,char>* f = new BiVertex<int,char>;
    f->type = false;
    f->value = 'f';
    graph.InsertVertex(f);
    BiVertex<int,char>* g = new BiVertex<int,char>;
    g->type = true;
    g->value = 'g';
    graph.InsertVertex(g);
    BiVertex<int,char>* h = new BiVertex<int,char>;
    h->type = false;
    h->value = 'h';
    graph.InsertVertex(h);
    graph.InsertUndirectEdge(a,b);
    graph.InsertUndirectEdge(a,d);
    graph.InsertUndirectEdge(c,d);
    graph.InsertUndirectEdge(e,f);
    graph.InsertUndirectEdge(c,f);
    graph.InsertUndirectEdge(g,h);
    graph.flow2match();
    return 0;
}
