#pragma once
// Multiple head file only include once

// Include libraries
#include <cmath>
// Include our head files
#include "../Class_FibNode/FibNode.h"


/*=================================*
 * Class: FibNode
 * Created by FDChick
 *---------------------
 * Class for Fibonacci heap
 *==================================*/
class FibHeap
{
protected:
	// Variables
	int numitems;		// number of all items
	//int maxDegree;		// max Degree of the nodes
	FibNode* min;		// min node of the heap

public:
	// Construct and destruct functions
	FibHeap();
	~FibHeap();

public:
	// return variables
	int getNumitems();
	//int getMaxDegree();
	FibNode* getMin();

public:
	// FibHeap operations
	void insert(FibNode* node, bool fc(FibNode*, FibNode*));
	//void combine(FibHeap* heap, bool fc(FibNode*, FibNode*));
	void reset_min(bool fc(FibNode*, FibNode*));
	FibNode* remove_min_tree(bool fc(FibNode*, FibNode*));
	void consolidate(bool fc(FibNode*, FibNode*));
	FibNode* pop_min(bool fc(FibNode*, FibNode*));
	void update(int id, bool fc(FibNode*, FibNode*));
	FibNode* delete_node(int id, bool fc(FibNode*, FibNode*));
};

