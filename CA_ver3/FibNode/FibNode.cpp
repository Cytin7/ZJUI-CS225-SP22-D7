#include "FibNode.h"

/*
 *
 * Created By FDChick on 2022/4/5
 * Here Are the functions to define
 * All the methods in the class
 * FibNode
 *
 */

 //
 // Construct Function
 //
FibNode::FibNode() : LeftSib(this),
RightSib(this),
Parent(NULL),
Child(NULL),
mark_status(false),
degree(0) {
	FibNode* LeftSib = this;
	FibNode* RightSib = this;
	// FibHeap node struct
	// Created by FDChick.
	// defining a circle sibling linked list.
	// Pointing to Parent and one of the Child node
	FibNode* Parent = NULL;
	FibNode* Child = NULL;
	// using when deleting node in the FibHeap.
	bool mark_status = false;
	// The degree of the node
	int degree = 0;
}

//
// Destruct function
//
FibNode::~FibNode() {
	cout << "one of the FibNode is leaving us... \n";
}

/*
 * set functions to modify
 * the private characters in FibNode class
 */

 //
 // void setLeftSib()
 //
void FibNode::setLeftSib(FibNode* node) {
	this->LeftSib = node;
	node->RightSib = this;
	return;
}

//
// void setRightSib()
//
void FibNode::setRightSib(FibNode* node) {
	this->RightSib = node;
	node->LeftSib = this;
	return;
}

//
// void setParent()
//
void FibNode::setParent(FibNode* node) {
	this->Parent = node;
	node->Child = this;
	return;
}

//
// void setChild()
//
void FibNode::setChild(FibNode* node) {
	this->Child = node;
	node->Parent = this;
	return;
}



FibNode* FibNode::getLeftSib() {
	return LeftSib;
}
FibNode* FibNode::getRightSib() {
	return RightSib;
}
//
// Pointing to Parent and one of the Child node
//
FibNode* FibNode::getParent() {
	return Parent;
}
FibNode* FibNode::getChild() {
	return Child;
}
int FibNode::getdegree() {
	return this->degree;
}
//
// ***********************************
// calc_priority_number() to calculate
// the priority number in the FibNode class
// Created By Peidong Yang.
// ***********************************
//

void FibNode::calc_priority_number()
//for different kinds of heaps (status 0-4), we need to give different priority numbers
//0 - main_heap: 
//    The most important criterion is the profession category followed by a ranking of age groups,
//    and further followed by data and time of the registration.
//    priority_number is an integer 
//    position:    6           5         4 3     2 1
//    meaning:profession   age_group    month    day
//1 - ddl_heap: use deadline
//2 - medium_risk_heap: 1 month*2 = 60 halfdays
//3 - high_risk_heap: current time
//4 - withdraw_heap: 14*2 = 28 halfdays

{
	if (this->status == 0)
	{
		tm tmp;
		struct tm* info = &tmp;
		gmtime_s(info, &(this->reg_time));
		int month = info->tm_mon;
		int day = info->tm_mday;
		this->priority_number = (this->profession) * 100000 + (this->age_group) * 10000 + month * 100 + day * 1;
	}
	else if (this->status == 1)
	{
		tm tmp;
		struct tm* info = &tmp;
		gmtime_s(info, &(this->reg_time));
		int month = info->tm_mon;
		int day = info->tm_mday;
		this->priority_number = month * 100 + day * 1;
	}
	else if (this->status == 2)
	{
		this->priority_number = 60;
	}
	else if (this->status == 3)
	{
		tm tmp;
		struct tm* info = &tmp;
		gmtime_s(info, &(this->reg_time));
		int month = info->tm_mon;
		int day = info->tm_mday;
		this->priority_number = month * 100 + day * 1;
	}
	else if (this->status == 4)
	{
		this->priority_number = 28;
	}
}
//
// Method in the deletion
// on priority
//
void FibNode::set_priority_number(int a) {
	this->priority_number = a;
	return;
}
int FibNode::get_priority_number() {
	return priority_number;
}
void FibNode::priority_change() {
	this->priority_number = -1;
	return;
}

// Deepcopy the FibNode
// Added by CYTIN
FibNode* FibNode::deepcopy()
{
	FibNode new_fib;
	new_fib.address = this->address;
	new_fib.age = this->age;
	new_fib.age_group = this->age_group;
	new_fib.appoint_time = this->appoint_time;
	new_fib.birth = this->birth;
	new_fib.deadline = this->deadline;
	new_fib.degree = this->degree;
	new_fib.email = this->email;
	new_fib.hospital = this->hospital;
	new_fib.id = this->id;
	new_fib.name = this->name;
	new_fib.phone = this->phone;
	new_fib.priority = this->priority;
	new_fib.priority_number = this->priority;
	new_fib.profession = this->profession;
	new_fib.registry = this->registry;
	new_fib.reg_time = this->reg_time;
	new_fib.risk = this->risk;
	new_fib.status = this->status;
	new_fib.wechat = this->wechat;
	return &new_fib;
}