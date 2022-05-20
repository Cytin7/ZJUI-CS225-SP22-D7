//
//  union.h
//  
//
//  Created by TK on 14.05.22.
//

#ifndef union_h
#define union_h


#include<iostream>
using namespace std;
/*
    HW10 T4(2):
    Implement a partition data structure (aka union-find data structure) to support your
implementation in (i). For this use a list L, in which entries correspond to vertices. If
L[i] = j, then vertex i is in the connected component of j. In this way each connected
component is represented as a tree, so can easily check if the endpoints of the current edge
under consideration are already in the same connected component. Show how to realise
the merging of connected components.

*/
class UF
{
private:
// Number of Connected Component
    int count;
// List of node parent
    int parent[100];   // 
// Store tree's size
    int size[100];
public:
    UF(int n);
    ~UF();
    void union_pq(int p, int q);
    bool connected(int p, int q);
    int get_count();
    int find(int x);
    int find1(int x); // Better find function
    void display(int m);
    void cut(int p, int q);
};
// Construction function of Union&Find
// Other function is written in union_f.h (function)
UF::UF(int n)
{
    count = n;
    //parent=(int *)realloc(parent);
   // size[n];
    for(int i= 0; i < n;i++){ 
        parent[i] = i;
        size[i] = 1;
    }
    return;
}
#endif 