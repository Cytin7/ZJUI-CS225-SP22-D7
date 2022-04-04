#pragma once
#include <iostream>
#include <ctime>
using namespace std;

// global variables
time_t current_time = time(NULL);

// functions that will be used


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
	int reg_place;             // register place code
    time_t reg_time;           // regist time
	time_t appoint_time;       // appointment time
	int hospital;              // appointed hospital code
public:
	Record();
	~Record();

	// set Record data
	void setRecordData(int id, string name, string address, string phone, string wechat, string email, time_t birth, int profession, int risk, int reg_place);
	// set Record data by part
	void setRecordID(int id);
	void setRecordName(string name);
	void setRecordAddress(string address);
	void setRecordPhone(string phone);
	void setRecordWeChat(string wechat);
	void setRecordEmail(string email);
	void setRecordBirth(time_t birth);
	void setRecordProfession(int profession);
	void setRecordRisk(int risk);
	void setRecordRegisterPlace(int reg_place);
    void setRecordRegisterTime(time_t reg_time);
private:

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
