#pragma once
// Multiple head file only include once


// Include our head files
#include "../Record/Record.h"

/*========================================*
 * Class: FibNode
 *
 * Created by FDChick
 *--------------------
 * Introduction:
 *     Fibonacci heap node structure
 *========================================*/
class FibNode :public Record {
public:
	FibNode();
	~FibNode();
	// FibHeap node struct
	// Created by FDChick.
	// defining a circle sibling linked list.
	void setLeftSib(FibNode* node);
	void setRightSib(FibNode* node);
	// Pointing to Parent and one of the Child node
	void setParent(FibNode* node);
	void setChild(FibNode* node);
	FibNode* getLeftSib();
	FibNode* getRightSib();
	// Pointing to Parent and one of the Child node
	FibNode* getParent();
	FibNode* getChild();
	// 计算优先级的值
	int get_priority_number();
	void calc_priority_number();
	void set_priority_number(int a);
	int getdegree();
	// The degree of the node
	int degree;
	// using when deleting node in the FibHeap.
	bool mark_status;
private:
	// FibHeap node struct
	// Created by FDChick.
	// defining a circle sibling linked list.
	int priority_number;
	FibNode* LeftSib;
	FibNode* RightSib;
	// Pointing to Parent and one of the Child node
	FibNode* Parent;
	FibNode* Child;
public:
	int status;   // in which heap the node is in
	FibNode* deepcopy();   // Added by CYTIN, deepcopy the node and return a pointer.

// Added because of debugging
public:
	void priority_change();
	void MinusOne();
};