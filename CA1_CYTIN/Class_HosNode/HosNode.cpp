#include "HosNode.h"

// construct functon of class PNode
HosNode::HosNode()
{
	this->forward = NULL;
	this->backward = NULL;
	this->is_dummy = false;
	this->dummy = NULL;
	this->index = 0;
	this->capacity = 7;
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
//HosNode* HosNode::setReadBool(bool all_read)
//{
//	this->all_read = all_read;
//	return this;
//}
//HosNode* HosNode::setFile(ofstream& out_file)
//{
//	this->file = &out_file;
//	return this;
//}
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
	this->list = NULL;
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
	this->forward = NULL;
	this->backward = NULL;
	this->is_dummy = false;
	this->dummy = NULL;

	ListNode* list = new ListNode;
	(*list).setDummy();
	(*this).list = list;

	this->capacity = 7;
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
//bool HosNode::getReadBool()
//{
//	return this->all_read;
//}
//ofstream* HosNode::getFile()
//{
//	return this->file;
//}
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
	this->dummy = NULL;
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
		return NULL;
	}
	if (this != node->dummy) {
		cerr << "Error: Removing node from irrelevant list" << endl;
		return NULL;
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
	if (!(new_node->dummy == NULL)) {
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
