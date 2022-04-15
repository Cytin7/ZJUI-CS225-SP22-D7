#pragma once
// Multiple head file only include once

// Include libraries

// Include our head files
#include "../Class_Record/Record.h"

/*=================================*
 * Class: FibNode
 * Created by FDChick
 *---------------------
 * Node of Fibonacci Heap
 * Used for priority queue
 *==================================*/
class FibNode
{
protected:
	// Variables
	FibNode* left;		// pointer to right sibling
	FibNode* right;		// pointer to right sibling
	FibNode* parent;	// pointer to parent node
	FibNode* child;		// pointer to one of the children node
	int degree;			// number of children nodes
	bool mark;			// Marked if one of the children is deleted
	Record* record;		// Record data

public:
	// Construct and destruct functions
	FibNode();
	FibNode(Record* record);
	~FibNode();

public:
	// set Record data by each variable
	void setLeft(FibNode* left);
	void setRight(FibNode* right);
	void setParent(FibNode* parent);
	void setChild(FibNode* child);
	void setDegree(int degree);
	void setMark(bool mark);
	void setRecord(Record* record);
	// get Record data by each variable
	FibNode* getLeft();
	FibNode* getRight();
	FibNode* getParent();
	FibNode* getChild();
	int getDegree();
	bool getMark();
	Record* getRecord();

public:
	// Fibnode operations
	void append(FibNode* node);
	void addChild(FibNode* root);
	void concat(FibNode* root);
	void removeTree(FibNode* root);
	FibNode* idsearch(int id);
	int updateDegree();
};

