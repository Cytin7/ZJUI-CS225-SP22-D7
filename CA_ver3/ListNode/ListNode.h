#pragma once
// Multiple head file only include once

// Include our head files
#include "../Record/Record.h"

/*========================================
 * Class: ListNode
 * -----------------
 * created by CYTIN
 *
 * Introduction:
 *	The basis of queues.
 *  Both registry and
 *========================================*/
class ListNode : public Record
{
	//public:
	//	// For file input and output
	//	fstream* file;
protected:
	ListNode* forward;
	ListNode* backward;
	bool is_dummy;       // Bool variable, true means it is a dummy node
	int length;          // Linked list len

	// For Hospital, add its variable
	int capacity;          // The maximal number a hospital can handle
	ListNode* last_week;   // the node has been pushed last week
	ListNode* last_month;  // the node has been pushed last month

	// For Registry, add its variable
	ListNode* old;         // the node has been pushed to the main heaps

public:
	// construct and destruct function
	ListNode();
	~ListNode();

	// For all nodes
public:
	ListNode* getForward();
	ListNode* getBackward();
	bool isDummy();

	// For the list(dummy node):
public:
	// Get List information
	int getLength();

	// Set the node as the dummy node of the list
	void setDummy();

	// append a new node to the list
	void append(ListNode* new_node);

	// delete the node from the list
	void deleteNode();
	void deleteNode(ListNode* node);

	// concat two lists
	void concat(ListNode* list2);

	// Set registry and hospital variables
	void setCapacity(int capacity);
	void setLastWeek(ListNode* last_week);
	void setLastMonth(ListNode* last_month);
	void setOld(ListNode* old);
	void setFile(fstream* file);

	// Get registry and hospital variables
	int getCapacity();
	ListNode* getLastWeek();
	ListNode* getLastMonth();
	ListNode* getOld();
	//fstream* getFile();
};