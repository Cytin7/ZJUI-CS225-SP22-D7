#include "../head.h"

ListNode::ListNode()
{
	this->forward = NULL;
	this->backward = NULL;
	this->is_dummy = false;
	this->length = 0;

	this.
}

ListNode::~ListNode()
{
}

void ListNode::setDummy()
{
	// set the node as dummy node to create a new list
	this->is_dummy = true;
	this->length = 0;
	this->forward = this;
	this->backward = this;
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
