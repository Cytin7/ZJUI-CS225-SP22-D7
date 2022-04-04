#pragma once
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;

// global variables
time_t current_time = time(NULL);

// functions that will be used
tm time_diff(time_t* time1, time_t* time2); // calculate time difference
string genProfRome(const int& prof);        // generate Rome format of profession data


/* ---------------------------------------
 * class: Record
 *
 * created by CYTIN
 *
 * Introduction:
 *	Store all data of a recoord.
 * --------------------------------------- */
class Record
{
	// variables
protected:
	int id;                    // id of the patient
	string name;               // name of the patient
	string address;            // family address
	string phone;              // phone number
	string wechat;             // WeChat number
	string email;              // e-mail address
	time_t birth;              // date of birth
	int age;                   // age
	int age_group;             // age group (0~6)
	int profession;            // profession code (0~7)
	int risk;                  // risk status (0~3)
	time_t deadline;           // deadline 
	int priority;              // priority, used for the priority queue
	int registry;              // register place code
	time_t reg_time;           // time registered
	time_t appoint_time;       // appointment time
	int hospital;              // appointed hospital code
public:
	// construct and destruct function
	Record();
	~Record();

	// set Record data
	void setRecordData(int id, string name, string address, string phone, string wechat, string email, time_t birth, int profession, int risk, int registry);
	// set Record data for each variable
	void setRecordID(int id);
	void setRecordName(string name);
	void setRecordAddress(string address);
	void setRecordPhone(string phone);
	void setRecordWeChat(string wechat);
	void setRecordEmail(string email);
	void setRecordBirth(time_t birth);
	void setRecordProfession(int profession);
	void setRecordRisk(int risk);
	void setRecordRegistry(int registry);
	void setRecordRegisterTime(time_t reg_time);
};

/* ---------------------------------------
 * class: ListNode
 *
 * created by CYTIN
 *
 * Introduction:
 *	The basis of queues.
 *  Both registry and
 * --------------------------------------- */
class ListNode : public Record
{
protected:
	ListNode* forward;
	ListNode* backward;
	bool is_dummy;
	int length;

public:
	// construct and destruct function
	ListNode();
	~ListNode();

	// For the list(dummy node):
public:
	// Set the node as the dummy node of the list
	void setDummy();

	// append a new node to the list
	void append(ListNode* new_node);

	// delete the node from the list
	void deleteNode();
	void deleteNode(ListNode* node);

	// concat two lists
	void concat(ListNode* list2);
};


//
// FibHeap Created By FDChick 17:14 4.4.22.
//
//
// Class FibNode of the FibHeap.

class FibNode :public Record{
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
    // Mark
    void mark();
    FibNode* getLeftSib();
    FibNode* getRightSib();
    // Pointing to Parent and one of the Child node
    FibNode* getParent();
    FibNode* getChild();
    // using when deleting node in the FibHeap.
    bool is_marked();
private:
    // FibHeap node struct
    // Created by FDChick.
    // defining a circle sibling linked list.
    FibNode* LeftSib;
    FibNode* RightSib;
    // Pointing to Parent and one of the Child node
    FibNode* Parent;
    FibNode* Child;
    // using when deleting node in the FibHeap.
    bool mark_status;
    // The degree of the node
    int degree;
};

//
// Class FibHeap defining operations.
//
class FibHeap{
public:
    // construct & distruct
    FibHeap();
    ~FibHeap();

    // Operations for insertion.
    // To insert the new node just before the root linked list.
    // Then compare min and this node,
    // if the node is smaller,
    // then refresh the min to be the insert node.

    /* The Fib_Node_Add is used to complete the linked list operation.
     * And the Insert is truly insertion. */
    void Add_Node(FibNode* node, FibNode* root);
    void Insert(FibNode);

    // Operations for Concat.
    // to put one of the root linked list
    // to the current root linked list.
    // This is the same as to concat two double linked list.
    void Concat_Node(FibNode* node1, FibNode* node2);
    void Union_Heap(FibHeap* heap);

    // Operation to pop out the min node.
    // Directly to connect the min-node's sub-tree in to root list.
    // concat all the trees that has the same degree until
    // there is no trees have the same degree.
    FibNode* Pop_Min();
    /*
     * These Three are the operation to
     * consolidate the trees that have
     * the same degrees.
     */
    void link_Node(FibNode* node, FibNode* root);
    void Cons_Make();
    void Consolidate();

    // Delete the node.
    void Delete_Node(FibNode* node);

private:
    int numitems;
    int maxDegree;
    FibNode* min;
    FibNode** cons;
};
