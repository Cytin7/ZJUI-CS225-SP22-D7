#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <conio.h>
using namespace std;

// global variables
time_t current_time = time(NULL);
const time_t HALF_DAY = 43200;              // half day is 43200 seconds

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
	int registry;             // register place code
	time_t reg_time;           // regist time
	time_t appoint_time;       // appointment time
	int hospital;              // appointed hospital code
public:
	Record();
	~Record();

	// set Record data
	void setRecordData(int id, string name, string address, string phone, string wechat, string email, time_t birth, int profession, int risk, int registry);
	// set Record data by variables
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

	// get Record data by variables
	int getRecordID();
	string getRecordName();
	string getRecordAddress();
	string getRecordPhone();
	string getRecordWeChat();
	string getRecordEmail();
	time_t getRecordBirth();
	int getRecordAge();
	int getRecordAgeGroup();
	int getRecordProfession();
	int getRecordRisk();
	int getRecordRegistry();
	int getRecordRegisterTime();
	time_t fetRecordDeadline();
	int getRecordPriority();
	time_t getRecordAppointTime();
	int getRecordHospital();

private:

};

/* ---------------------------------------
 * class: ListNode
 *
 * created by CYTIN
 *
 * Introduction:
 *	The basis of queues.
 *  Both registry and
 * ---------------------------------------
 */
class ListNode : public Record
{
protected:
	ListNode* forward;
	ListNode* backward;
	bool is_dummy;       // Bool variable, true means it is a dummy node
	int length;          // Linked list len

	// For Hospital, add this variable
	int capacity;          // The maximal number a hospital can handle
	ListNode* last_week;   // the node has been pushed last week
	ListNode* last_month;  // the node has been pushed last month

	// For Registry, add this variable
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

	// Get registry and hospital variables
	int getCapacity();
	ListNode* getLastWeek();
	ListNode* getLastMonth();
	ListNode* getOld();
};


//
// FibHeap Created By FDChick 17:14 4.4.22.
//
//
// Class FibNode of the FibHeap.

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
	// Mark
	void mark();
	FibNode* getLeftSib();
	FibNode* getRightSib();
	// Pointing to Parent and one of the Child node
	FibNode* getParent();
	FibNode* getChild();
	// 计算优先级的值
	int get_priority_number();
	void calc_priority_number();
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
};

//
// Class FibHeap defining operations.
//
class FibHeap {
public:
	// construct & deconstruct
	FibHeap();
	~FibHeap();
	// 移除某个节点出双链表
	void removeNode(FibNode* node);
	// Operations for insertion.
	// To insert the new node just before the root linked list.
	// Then compare min and this node,
	// if the node is smaller,
	// then refresh the min to be the insert node.
	/* The Fib_Node_Add is used to complete the linked list operation.
	 * And the Insert is truly insertion. */
	void Add_Node(FibNode* node, FibNode* root);
	// 通过节点指针插入节点
	void Insert(FibNode* node);
	// 移除斐波那契堆中的最小节点
	void removeMin();
	// 将other合并到当前堆中
	void combine(FibHeap* other);
	// 将斐波那契堆中的node更新为newkey
	void update(FibNode* node);
	// 更新斐波那契堆的节点node的键值为key
	void update(int id);
	// 删除结点node
	void remove(FibNode* node);
	// 打印斐波那契堆!
	void print();
	// 销毁
	void destroy();

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
	// renew the degree.
	void renewDegree(FibNode* parent, int degree);
	void Cons_Make();
	void Consolidate();
	// 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
	void cut(FibNode* node, FibNode* parent);
	// 对节点node进行"级联剪切"
	void cascadingCut(FibNode* node);
	// 将斐波那契堆中节点node的值减少为key
	void decrease(FibNode* node, int key);
	// 将斐波那契堆中节点node的值增加为key
	void increase(FibNode* node, int key);
	// 遍历查找键值为key的节点
	FibNode* idsearch(int id);
private:
	// 销毁斐波那契堆
	void destroyNode(FibNode* node);
	// 打印斐波那契堆
	void print(FibNode* node, FibNode* prev, int direction);
	// some characters.
	int numitems;
	int maxDegree;
	FibNode* min;
	FibNode** cons;
};

/* ---------------------------------------
 * class: PointerNode
 *
 * created by CYTIN
 *
 * Introduction:
 *	For list of pointers;
 * --------------------------------------- */
template <class T>
class PNode
{
protected:
	PNode* dummy;
	PNode* forward;
	PNode* backward;
	bool is_dummy;
	int length;
	T* pointer;

public:
	PNode();
	~PNode();
	void set_dummy();
	void set_member(T* handle);
	void append(T* handle);
	void deleteNode();

private:

};

class Registry:public PNode<ListNode>
{
	fstream* input_file;

};


