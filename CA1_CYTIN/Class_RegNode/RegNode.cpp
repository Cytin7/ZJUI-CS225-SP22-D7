#include "RegNode.h"

RegNode::RegNode()
{
	(*this).index = 0;
	(*this).forward = nullptr;
	(*this).backward = nullptr;
	(*this).is_dummy = false;
	(*this).dummy = nullptr;
	(*this).list = nullptr;
	//(*this).file = nullptr;
	(*this).max_read = 0;
	(*this).min_read = 0;
	(*this).length = 0;
}

// destruct function of class PNode
RegNode::~RegNode()
{
}

// set RegNode data by each variable
RegNode* RegNode::setIndex(int index)
{
	(*this).index = index;
	return this;
}
RegNode* RegNode::setForward(RegNode* forward)
{
	(*this).forward = forward;
	return this;
}
RegNode* RegNode::setBackward(RegNode* backward)
{
	(*this).backward = backward;
	return this;
}
RegNode* RegNode::setDummyBool(bool is_dummy)
{
	(*this).is_dummy = is_dummy;
	return this;
}
RegNode* RegNode::setDummyNode(RegNode* dummy)
{
	(*this).dummy = dummy;
	return this;
}
RegNode* RegNode::setList(ListNode* list)
{
	(*this).list = list;
	return this;
}
//RegNode* RegNode::setFile(fstream* fileptr)
//{
//	FileIO tmp(fileptr);
//	(*this).file = &tmp;
//	return this;
//}
RegNode* RegNode::setMax(int max_read)
{
	(*this).max_read = max_read;
	return this;
}
RegNode* RegNode::setMin(int min_read)
{
	(*this).min_read = min_read;
	return this;
}
RegNode* RegNode::setLength(int length)
{
	(*this).length = length;
	return this;
}

/*=================================*
 * Method: RegNode::setDummy
 * Created by CYTIN
 *--------------------------
 * Set the node as a dummy node
 *==================================*/
RegNode* RegNode::setDummy()
{
	(*this).forward = this;
	(*this).backward = this;
	(*this).is_dummy = true;
	(*this).dummy = this;
	(*this).list = nullptr;
	//(*this).file = nullptr;
	(*this).max_read = 0;
	(*this).min_read = 0;
	(*this).length = 0;
	return this;
}

/*=================================*
 * Method: RegNode::setData
 * Created by CYTIN
 *--------------------------
 * Set the node as a data node
 *==================================*/
RegNode* RegNode::setData(int index)//fstream* fileptr)
{
	(*this).index = index;
	(*this).forward = nullptr;
	(*this).backward = nullptr;
	(*this).is_dummy = false;
	(*this).dummy = nullptr;
	ListNode* list = new ListNode;
	(*list).setDummy();
	(*this).list = list;

	//FileIO
	//FileIO tmpfile(fileptr);
	//(*this).file = &tmpfile;

	(*this).max_read = 10;
	(*this).min_read = 5;
	(*this).length = 0;

	return this;
}

// get RegNode data by each variable
int RegNode::getIndex()
{
	return (*this).index;
}
RegNode* RegNode::getForward()
{
	return (*this).forward;
}
RegNode* RegNode::getBackward()
{
	return (*this).backward;
}
bool RegNode::getDummyBool()
{
	return (*this).is_dummy;
}
RegNode* RegNode::getDummyNode()
{
	return (*this).dummy;
}
ListNode* RegNode::getList()
{
	return (*this).list;
}
//FileIO* RegNode::getFile()
//{
//	return (*this).file;
//}
int RegNode::getMax()
{
	return (*this).max_read;
}
int RegNode::getMin()
{
	return (*this).min_read;
}
int RegNode::getLength()
{
	return (*this).length;
}

/*=================================*
 * Method: RegNode::remove
 * Created by CYTIN
 *--------------------------
 * Remove the node form its list
 *==================================*/
void RegNode::remove()
{
	if ((*this).is_dummy) {
		cerr << "Error: Removing dummy node" << endl;
		return;
	}
	(*(*this).dummy).length -= 1;
	(*(*this).backward).forward = (*this).forward;
	(*(*this).forward).backward = (*this).backward;
	(*this).dummy = nullptr;
}

/*=================================*
 * Method: RegNode::remove
 * Created by CYTIN
 *--------------------------
 * Remove the node form the list
 *==================================*/
RegNode* RegNode::remove(RegNode* node)
{
	if ((*node).is_dummy) {
		cerr << "Error: Removing dummy node" << endl;
		return nullptr;
	}
	if (this != (*node).dummy) {
		cerr << "Error: Removing node from irrelevant list" << endl;
		return nullptr;
	}
	else {
		(*node).remove();
	}
	return this;
}

/*=================================*
 * Method: RegNode::append
 * Created by CYTIN
 *--------------------------
 *   Append the new node to the
 * end of list.
 *==================================*/
RegNode* RegNode::append(RegNode* new_node)
{
	if ((*new_node).is_dummy) {
		cerr << "Error: Cannot append a dummy node" << endl;
		return this;
	}
	// check if it is already in a list
	if (!((*new_node).dummy == nullptr)) {
		(*new_node).remove();
	}
	if ((*this).is_dummy) {
		(*this).length += 1;
		(*new_node).backward = (*this).backward;
		(*new_node).forward = this;
		(*(*this).backward).forward = new_node;
		(*this).backward = new_node;
		(*new_node).dummy = this;
	}
	else {
		(*this).dummy > append(new_node);
	}
	return this;
}

/*=================================*
 * Method: RegNode::readRecord
 * Created by CYTIN
 *--------------------------
 *   Read data from files and append
 * list. If EOF, then do nothing.
 *==================================*/
 //void RegNode::readRecord(time_t current_time)
 //{
 //	//if ((*(*this).file).isEOF()) {
 //	//	cout << "File already ended." << endl;
 //	//	return;
 //	//}
 //	string data;
 //	int record_number = rand() % ((*this).max_read - (*this).min_read + 1) + (*this).min_read;
 //	for (int i = 0; i < record_number; i++) {
 //		if ((*(*this).file).readline(data)) {
 //			ListNode* node = new ListNode;
 //			(*node).setRecord(dataLine2Record(data, current_time));
 //			(*(*this).list).append(node);
 //		}
 //		else {
 //			break;
 //		}
 //	}
 //	return;
 //}

 /*====================================*
  * Method: RegNode::printAllRecords
  * Created by CYTIN
  *--------------------------
  *   Display all record information
  *=====================================*/
void RegNode::printAllRecords()
{
	if ((*this).is_dummy) {
		cout << "No record to show for dummy node." << endl;
		return;
	}
	cout << strjust("", 201, '=') << endl;
	cout << "| " << strjust("ID", 6) << " | " << strjust("Name", 20)
		<< " | " << strjust("Phone Number", 16) << " | " << strjust("WeChat", 12)
		<< " | " << strjust("E-mail Address", 40) << " | " << strjust("Job", 6)
		<< " | " << strjust("Birthday", 16) << " | " << strjust("Risk", 6)
		<< " | " << strjust("Deadline", 16) << " | " << strjust("Address", 32) 
		<<" |" << endl;
	cout << strjust("|", 200, '-') << "|" << endl;
	ListNode* node = (*(*this).list).getForward();
	while (!(*node).getDummyBool()) {
		cout << (*node).recordInfo() << endl;
		node = (*node).getForward();
	}
	cout << strjust("", 201, '=') << endl;
	return;
}