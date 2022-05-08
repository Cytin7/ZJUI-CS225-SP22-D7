#pragma once
// Multiple head file only include once

// Include libraries

// Include our head files
#include "../Class_ListNode/ListNode.h"

/*=================================*
 * Class: HosNode
 * Created by CYTIN
 *---------------------
 *   Node of doubly linked pointer
 * list, used for hospitals.
 *==================================*/
class HosNode
{
	// Variables
protected:
	HosNode* forward;
	HosNode* backward;
	bool is_dummy;          // Bool variable, true means it is a dummy node
	HosNode* dummy;
	// For data node:
	ListNode* list;         // the list of all records
	int capacity;           // capacity of the hospital
	int index;
	// For dummy node:
	int length;             // Linked list length

// Construct and destruct functions
public:
	HosNode();
	~HosNode();

public:
	// set HosNode data by each variable
	HosNode* setForward(HosNode* forward);
	HosNode* setBackward(HosNode* backward);
	HosNode* setDummyBool(bool is_dummy);
	HosNode* setDummyNode(HosNode* dummy);
	HosNode* setList(ListNode* list);
	HosNode* setCapacity(int capacity);
	HosNode* setIndex(int index);
	HosNode* setLength(int length);

	// get HosNode data by each variable
	HosNode* getForward();
	HosNode* getBackward();
	bool getDummyBool();
	HosNode* getDummyNode();
	ListNode* getList();
	int getCapacity();
	int getIndex();
	int getLength();

public:
	// Node setup functions
	HosNode* setDummy();
	HosNode* setData(int index);

	// List operations
	void remove();
	HosNode* remove(HosNode* node);
	HosNode* append(HosNode* new_node);

};

