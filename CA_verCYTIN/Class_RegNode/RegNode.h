#pragma once
// Multiple head file only include once

// Include libraries

// Include our head files
#include "../Class_ListNode/ListNode.h"
#include "../str_funcions/str_funcions.h"

/*=================================*
 * Class: RegNode
 * Created by CYTIN
 *---------------------
 *   Node of doubly linked pointer
 * list, used for registries.
 *==================================*/
class RegNode
{
	// Variables
protected:
	RegNode* forward;
	RegNode* backward;
	bool is_dummy;          // Bool variable, true means it is a dummy node
	RegNode* dummy;
	// For data node:
	int index;              // registry index
	ListNode* list;         // the list of all records
	//FileIO* file;         // input file stream
	int max_read;           // maxinum record input number for simulation
	int min_read;           // mininum record input number for simulation
	// For dummy node:
	int length;             // Linked list length

// Construct and destruct functions
public:
	//RegNode();
	RegNode();
	~RegNode();

public:
	// set RegNode data by each variable
	RegNode* setIndex(int index);
	RegNode* setForward(RegNode* forward);
	RegNode* setBackward(RegNode* backward);
	RegNode* setDummyBool(bool is_dummy);
	RegNode* setDummyNode(RegNode* dummy);
	RegNode* setList(ListNode* list);
	//RegNode* setFile(fstream* fs);
	RegNode* setMax(int max_read);
	RegNode* setMin(int min_read);
	RegNode* setLength(int length);

	// get RegNode data by each variable
	int getIndex();
	RegNode* getForward();
	RegNode* getBackward();
	bool getDummyBool();
	RegNode* getDummyNode();
	ListNode* getList();
	//FileIO* getFile();
	int getMax();
	int getMin();
	int getLength();

public:
	// Node setup functions
	RegNode* setDummy();
	RegNode* setData(int index);//fstream* fileptr);

	// List operations
	void remove();
	RegNode* remove(RegNode* node);
	RegNode* append(RegNode* new_node);

	// Read record data from file
	//void readRecord(time_t current_time);

	// Print Information
	void printAllRecords();

};

