//
//  union.h
//  
//
//  Created by TK on 14.05.22.
//


#include <iostream>
#include "union.h"


using std::cout;
using std::cin;
using std::endl;



void UF::display(int m){
    //int n = get_count();

    cout<< "Present Graph:"<<endl;

    for (int i = 0; i < m; i++)
    {
        cout<< "Node "<< i <<" has parent" << this->parent[i] << endl;
    }
    cout<<"-------------------------------------------"<<endl<<endl;
}


int UF::get_count(){
    return this->count;
}

bool UF::connected(int p, int q){
    int rootP = find(p);
    int rootQ = find(q);
    return rootP == rootQ;
}

int UF::find(int x){
    if(this->parent[x] != x){
        this->parent[x] = find(this->parent[x]);
    }
    return this->parent[x];
}
int UF::find1(int x){
// Better find function
    while (parent[x] != x) {

        x = parent[x];
    }
        return x;
}

void UF::union_pq(int p, int q){
    int rootP = find(p);
    int rootQ = find(q);

    if( rootP == rootQ){
        return;
    }else{
        parent[rootQ] = rootP;
        // union Q and P
        // // 小树接到大树下面，较平衡
        // if (size[rootP] > size[rootQ]) {
        //     parent[rootQ] = rootP;
        //     size[rootP] += size[rootQ];
        // } else {
        //     parent[rootP] = rootQ;
        //     size[rootQ] += size[rootP];
        // }    
    
    }
}
// Cut function, used to cut p and q
// but still need further consideration

void UF::cut(int p, int q){
    int rootP = find(p);
    int rootQ = find(q);

    if( rootP != rootQ){
        return; 
    }else{
        this->parent[rootQ] = q;
        this->parent[rootP] = p;

        // cut P and Q
        count++;
    }
}



