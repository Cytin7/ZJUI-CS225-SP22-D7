//
//  Kruskal.cpp
//  
//
//  Created by WangJie on 14.05.22.
//

#include<iostream>
#include<vector>
#include<algorithm>
#include"union.h"
#include"union_f.h"
using namespace std;
/*
    HW10 T4(i):
	Implement Kruskal algorithm.
	Here I use many STL, to focus on how to implement the algo itself.

*/

// a prepared test case
void testcase1();
// put in the graph by hand
void handmode();

struct edge // a structure storing the undirected edge
{
	int u, v; // id of 2 vertex
	int weight; 
	edge(){}
	edge(int uu,int vv,int weight1)
	{
		u=uu,v=vv,weight=weight1;
	}
};

// compare -- helper function of edge functor
bool compare(edge a, edge b)
{
	return a.weight < b.weight;
}

// Kruskal -- main algorithm
//    input -- 
void kruskal(int n, vector<edge> Edge)
{	
	UF *father = new UF(n);
	father->display(n);
	vector<int> result; // Store the outcome edges set of Kruskal

	// sort edge from small to big
	sort(Edge.begin(), Edge.end(), compare); 
	//Helper part to debug whether sort well
	cout<<"Sorted Edge List:" <<endl;
	for (int i = 0; i < Edge.size(); i++)
	{
		cout<<Edge[i].u <<" <-> ";
		cout<<Edge[i].weight <<" <-> ";
		cout<<Edge[i].v <<endl;
	}


	// read value, algo stop at n-1 because n vertexes has at most n-1 edges in the MST
	for (int i = 0; i < Edge.size() && result.size() < n-1 ; i++) 
	{
		int u = Edge[i].u -1;
		int v = Edge[i].v -1 ;
		cout<<" Start loop "<<i<<endl;


		if (!father->connected(u,v)) // Avoid circle in the tree
		{
			father->union_pq(u,v);

			cout<<Edge[i].u <<" <-> ";
			
			cout<<Edge[i].weight <<" <-> ";
			cout<<Edge[i].v <<endl;
			// Using i to record the edge we need
			result.push_back(i);

			father->display(n);
		}
		
		cout<<" Finished loop "<<i<<endl;

	}
	cout<<" YES Finished loop"<<endl;

	if (result.size() != n - 1)
	{
		cout << "Graph of size: " << result.size()  << " is not connected" << endl;
		return;
	}
	else
	{
		cout << "Each edge of the MST: " << endl;
		
		for (int i = 0; i < result.size(); ++i)
		{
			cout<<Edge[result[i]].u <<" <-> ";
			cout<<Edge[result[i]].weight <<" <-> ";
			cout<<Edge[result[i]].v <<endl;
			
		
		}	
	}
}

int main()
{
	cout<< "Selecting mode... "<<endl<<"1 for handmode, 2 for testcase1: ";

	int mode;
	cin >> mode;

	switch (mode)
	{
	case 1:
		cout << "Handmode\n";
		handmode();

		break;
	
	default:
		cout << "TESTCASE1\n";

		testcase1();
		break;
	}

	

	cout<<"------------------E N D------------------"<<endl;
	
	return 0;
}
 

void testcase1(){
	int m = 5;
	int n = 4;
	vector<edge> Edge(m);

	Edge[0].u = 1;
	Edge[0].v = 2;
	Edge[0].weight = 1;

	Edge[1].u = 1;
	Edge[1].v = 3;
	Edge[1].weight = 5;

	Edge[2].u = 1;
	Edge[2].v = 4;
	Edge[2].weight = 4;
	
	Edge[3].u = 2;
	Edge[3].v = 3;
	Edge[3].weight = 2;

	Edge[4].u = 2;
	Edge[4].v = 4;
	Edge[4].weight = 3;


	kruskal(n,Edge);
}

void handmode(){
	int n, m;
	vector<edge> Edge(m);

	cout << "Please enter the number of vertex: ";
	cin >> n;
	cout << "\nPlease enter the number of edges: ";
	cin >> m;
	cout << "\nEnter the information of each edge:" << endl;
	cout << "|------------------|"<<endl;
	
	for (int i = 0; i < m; ++i)
	{
		cout<<" START->LENGTH->END" << endl;
		cin >> Edge[i].u >> Edge[i].weight >> Edge[i].v;
	}
	kruskal(n,Edge);
	return;
}

/*  Daily Poem
	Where the north wind meets the sea,
	there's a mother full of memory.
	Come, my darling, homeward bound
	When all is lost, then all is found.
						--- All is Found
							Robert Lopez
*/