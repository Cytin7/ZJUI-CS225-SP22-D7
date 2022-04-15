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
	bool all_read;          // if all records have been read, all_read = true
	ofstream* file;         // input file stream
	int capacity;           // capacity of the hospital
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
	HosNode* setReadBool(bool all_read);
	HosNode* setFile(ofstream& out_file);
	HosNode* setCapacity(int capacity);
	HosNode* setLength(int length);

	// get HosNode data by each variable
	HosNode* getForward();
	HosNode* getBackward();
	bool getDummyBool();
	HosNode* getDummyNode();
	ListNode* getList();
	bool getReadBool();
	ofstream* getFile();
	int getCapacity();
	int getLength();

public:
	// Node setup functions
	HosNode* setDummy();
	HosNode* setData();

	// List operations
	void remove();
	HosNode* remove(HosNode* node);
	HosNode* append(HosNode* new_node);

};

