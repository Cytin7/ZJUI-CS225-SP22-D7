#pragma once
// the degree of btree
#define M 2 
// Notice:
// The main body of BTree code is originated from "orange1438",
// his github repository ：BTree and BPlusTree Realize
// Link: https://github.com/orange1438/BTree-and-BPlusTree-Realize
// Due to the limit of time, our code is the modified version of it
// And applying to the CA2 project
// The program is based on Windows System
typedef struct btree_nodes {
	int k[2*M-1];
	struct btree_nodes *p[2*M];
	int num;
	bool is_leaf;
	struct btree_nodes *prev;  // use one struct just for simple
	struct btree_nodes *next;  // B+Tree used
	
} btree_node;


typedef struct StorageNode{
	btree_node bnode;
	int index[M];  //index_set 
}storage_node;

typedef struct StorageStruct{
	storage_node *snode;
	int len;
}storage_struct;
