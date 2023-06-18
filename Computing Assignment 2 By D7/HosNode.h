#pragma once
// Multiple head file only include once

// Include libraries

// Include our head files
#include "ListNode.h"

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
	int capacity;           // capacity of the hospital
	int index;
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
	HosNode* setCapacity(int capacity);
	HosNode* setIndex(int index);
	HosNode* setLength(int length);

	// get HosNode data by each variable
	HosNode* getForward();
	HosNode* getBackward();
	bool getDummyBool();
	HosNode* getDummyNode();
	ListNode* getList();
	int getCapacity();
	int getIndex();
	int getLength();
    void printAllRecords();

public:
	// Node setup functions
	HosNode* setDummy();
	HosNode* setData(int index);

	// List operations
	void remove();
	HosNode* remove(HosNode* node);
	HosNode* append(HosNode* new_node);

};

// construct functon of class PNode
HosNode::HosNode()
{
    this->forward = nullptr;
    this->backward = nullptr;
    this->is_dummy = false;
    this->dummy = nullptr;
    this->index = 0;
    this->capacity = 10;
    this->length = 0;
}

// destruct function of class PNode
HosNode::~HosNode()
{
}

// set HosNode data by each variable
HosNode* HosNode::setForward(HosNode* forward)
{
    this->forward = forward;
    return this;
}

HosNode* HosNode::setBackward(HosNode* backward)
{
    this->backward = backward;
    return this;
}

HosNode* HosNode::setDummyBool(bool is_dummy)
{
    this->is_dummy = is_dummy;
    return this;
}

HosNode* HosNode::setDummyNode(HosNode* dummy)
{
    this->dummy = dummy;
    return this;
}

HosNode* HosNode::setList(ListNode* list)
{
    this->list = list;
    return this;
}

HosNode* HosNode::setCapacity(int capacity)
{
    this->capacity = capacity;
    return this;
}
HosNode* HosNode::setIndex(int index)
{
    this->index = index;
    return this;
}
HosNode* HosNode::setLength(int length)
{
    this->length = length;
    return this;
}

/*=================================*
 * Method: HosNode::setDummy
 * Created by CYTIN
 *--------------------------
 * Set the node as a dummy node
 *==================================*/
HosNode* HosNode::setDummy()
{
    this->forward = this;
    this->backward = this;
    this->is_dummy = true;
    this->dummy = this;
    this->list = nullptr;
    this->capacity = 0;
    this->length = 0;
    return this;
}

/*=================================*
 * Method: HosNode::setData
 * Created by CYTIN
 *--------------------------
 * Set the node as a data node
 *==================================*/
HosNode* HosNode::setData(int index)
{
    this->index = index;
    this->forward = nullptr;
    this->backward = nullptr;
    this->is_dummy = false;
    this->dummy = nullptr;

    ListNode* list = new ListNode;
    (*list).setDummy();
    (*this).list = list;

    this->capacity = 10;
    this->length = 0;
    return this;
}

// get HosNode data by each variable
HosNode* HosNode::getForward()
{
    return this->forward;
}
HosNode* HosNode::getBackward()
{
    return this->backward;
}
bool HosNode::getDummyBool()
{
    return this->is_dummy;
}
HosNode* HosNode::getDummyNode()
{
    return this->dummy;
}
ListNode* HosNode::getList()
{
    return this->list;
}


int HosNode::getCapacity()
{
    return this->capacity;
}
int HosNode::getIndex()
{
    return this->index;
}
int HosNode::getLength()
{
    return this->length;
}

/*=================================*
 * Method: HosNode::remove
 * Created by CYTIN
 *--------------------------
 * Remove the node form its list
 *==================================*/
void HosNode::remove()
{
    if (this->is_dummy) {
        cerr << "Error: Removing dummy node" << endl;
        return;
    }
    this->dummy->length -= 1;
    this->backward->forward = this->forward;
    this->forward->backward = this->backward;
    this->dummy = nullptr;
}

/*=================================*
 * Method: HosNode::remove
 * Created by CYTIN
 *--------------------------
 * Remove the node form the list
 *==================================*/
HosNode* HosNode::remove(HosNode* node)
{
    if (node->is_dummy) {
        cerr << "Error: Removing dummy node" << endl;
        return nullptr;
    }
    if (this != node->dummy) {
        cerr << "Error: Removing node from irrelevant list" << endl;
        return nullptr;
    }
    else {
        node->remove();
    }
    return this;
}

/*=================================*
 * Method: HosNode::append
 * Created by CYTIN
 *--------------------------
 *   Append the new node to the
 * end of list.
 *==================================*/
HosNode* HosNode::append(HosNode* new_node)
{
    if (new_node->is_dummy) {
        cerr << "Error: Cannot append a dummy node" << endl;
        return this;
    }
    // check if it is already in a list
    if (!(new_node->dummy == nullptr)) {
        new_node->remove();
    }
    if (this->is_dummy) {
        this->length += 1;
        new_node->backward = this->backward;
        new_node->forward = this;
        this->backward->forward = new_node;
        this->backward = new_node;
        new_node->dummy = this;
    }
    else {
        this->dummy->append(new_node);
    }
    return this;
}

void HosNode::printAllRecords()
{
    if ((*this).is_dummy) {
        cout << "No record to show for dummy node." << endl;
        return;
    }
    cout << strjust("", 201, '=') << endl;
    cout << " | " << strjust("ID", 6) << " | " << strjust("Name", 20)
         << " | " << strjust("Phone Number", 16) << " | " << strjust("WeChat", 12)
         << " | " << strjust("E-mail Address", 40) << " | " << strjust("Job", 6)
         << " | " << strjust("Birthday", 16) << " | " << strjust("Risk", 6)
         << " | " << strjust("Deadline", 16) << " | " << strjust("Address", 32)
         << " | " << endl;
    cout << strjust("|", 200, '-') << "|" << endl;
    ListNode* node = (*(*this).list).getForward();
    while (!(*node).getDummyBool()) {
        cout << (*node).recordInfo() << endl;
        node = (*node).getForward();
    }
    cout << strjust("", 201, '=') << endl;
    return;
}

