#include "../head.h"

ListNode::ListNode()
{
	this->forward = NULL;
	this->backward = NULL;
	this->is_dummy = false;
	this->length = 0;

	this->capacity = 0;
	this->last_week = NULL;
	this->last_month = NULL;
	this->old = NULL;
}

ListNode::~ListNode()
{
}

ListNode* ListNode::getForward()
{
	return this->forward;
}
ListNode* ListNode::getBackward()
{
	return this->backward;
}
bool ListNode::isDummy()
{
	return this->is_dummy;
}

void ListNode::setDummy()
{
	// set the node as dummy node to create a new list
	this->is_dummy = true;
	this->length = 0;
	this->forward = this;
	this->backward = this;
	this->capacity = 0;
	this->last_week = this;
	this->last_month = this;
	this->old = this;
}

void ListNode::append(ListNode* new_node)
{
	// Test if the node is the nummy node
	if (this->is_dummy) {
		// if the node is dummy node, append new node to the end of the list
		new_node->forward = this;
		new_node->backward = this->backward;
		this->backward->forward = new_node;
		this->backward = new_node;
	}
	else {
		// if the node is not a dummy node, append new node forward
		new_node->forward = this->forward;
		new_node->backward = this;
		this->forward->backward = new_node;
		this->forward = new_node;
	}
}

void ListNode::deleteNode()
{
	if (this->is_dummy) {
		cout << "You are about to delete the whole list. Confirm the operation? [Y/n]" << endl;
		int ch;
		while (true) {
			if (_kbhit()) {
				ch = _getch();
				cout << ch;
				// get the input key and check
				if ((ch == 89) || (ch == 100)) {
					// if input "Y" or press Enter
					ListNode* node = this->forward;
					while (!node->is_dummy) {
						node = node->forward;
						node->backward->deleteNode();
					}
					delete[] this;
				}
				else {
					break;
				}
			}
		}
	}
	else {
		delete[] this;
	}
}
void ListNode::deleteNode(ListNode* node) 
{
	this->length = this->length - 1;
	node->backward->forward = node->forward;
	node->forward->backward = node->backward;
	node->deleteNode();
}


void ListNode::concat(ListNode* list2)
{
	// test if the node id dummy node, if not, raise error
	if (!this->is_dummy) {
		cerr << "Concat Error: Trying to cancat a data node" << endl;
		return;
	}
	// Test if the node to cancat is a dummy node. if not, raise error
	if (!list2->is_dummy) {
		cerr << "Concat Error: Trying to cancat with a data node" << endl;
		return;
	}
	else {
		this->backward->forward = list2->forward;
		list2->forward->backward = this->backward->forward;
		this->backward = list2->backward;
		list2->backward->forward = this;
		this->length = this->length + list2->length;
		// set list2 to empty list
		list2->forward = list2;
		list2->backward = list2;
		list2->length = 0;
	}
}

// Set registry and hospital variables
void ListNode::setCapacity(int capacity)
{
	this->capacity = capacity;
}
void ListNode::setLastWeek(ListNode* last_week)
{
	this->last_week = last_week;
}
void ListNode::setLastMonth(ListNode* last_month)
{
	this->last_month = last_month;
}
void ListNode::setOld(ListNode* old)
{
	this->old = old;
}

// Get registry and hospital variables
int ListNode::getCapacity()
{
	return this->capacity;
}
ListNode* ListNode::getLastWeek()
{
	return this->last_week;
}
ListNode* ListNode::getLastMonth()
{
	return this->last_month;
}
ListNode* ListNode::getOld()
{
	return this->old;
}