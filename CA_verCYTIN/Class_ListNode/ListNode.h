#pragma once
// Multiple head file only include once

// Include libraries

// Include our head files
#include "../Class_Record/Record.h"
#include "../str_funcions/str_funcions.h"
#include "../Class_FibNode/FibNode.h"


// global variables
extern const int reg_num;

/*=================================*
 * Class: ListNode
 * Created by CYTIN
 *---------------------
 * Node of doubly linked record list
 * Used for registries and hospitals
 *==================================*/
class ListNode
{
protected:
	// Variables
	ListNode* forward;
	ListNode* backward;
	bool is_dummy;          // Bool variable, true means it is a dummy node
	// For data node:
	Record* record;
	ListNode* dummy;
	// For dummy node:
	int length;             // Linked list length
	ListNode* old;			// Pointer to last sent record node
	ListNode* last_month;	// Pointer to last month report node
	ListNode* last_week;	// Pointer to last week report node

// Construct and destruct functions
public:
	ListNode();
	~ListNode();


public:
	// set variables
	ListNode* setForward(ListNode* forward);
	ListNode* setBackward(ListNode* backward);
	ListNode* setDummyBool(bool is_dummy);
	ListNode* setRecord(Record* record);
	ListNode* setRecordwithData(string dataline,int reg_index, time_t current_time);
	ListNode* setDummyNode(ListNode* dummy);
	ListNode* setLength(int length);
	ListNode* setOld(ListNode* old);
	ListNode* setLastMonth(ListNode* last_month);
	ListNode* setLastWeek(ListNode* last_week);

	// set the node as dummy node
	ListNode* setDummy();

	// get variables
	ListNode* getForward();
	ListNode* getBackward();
	bool getDummyBool();
	Record* getRecord();
	ListNode* getDummyNode();
	int getLength();
	ListNode* getOld();
	ListNode* getLastMonth();
	ListNode* getLastWeek();

	// List operations
	void remove();
	ListNode* remove(ListNode* node);
	ListNode* append(ListNode* new_node);
	ListNode* insert(ListNode* new_node);
	ListNode* pop();
	ListNode* drop();
	ListNode* find(int index);
	ListNode* shift(int displace);
	ListNode* idsearch(int id);

	// copy the node
	ListNode* copy();
	ListNode* deepcopy();
	FibNode* toFibNode();

	// Print information
	string recordInfo();

};