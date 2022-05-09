#include "ListNode.h"

// construct functon of class ListNode
ListNode::ListNode()
{
	// Initialize all variables
	// Linked List
	(*this).forward = nullptr;
	(*this).backward = nullptr;
	(*this).is_dummy = false;
	// Data
	Record* empty_record = new Record;
	(*this).record = empty_record;
	(*this).dummy = nullptr;
	// Dummy
	(*this).length = 0;
	(*this).old = nullptr;
	(*this).last_week = nullptr;
	(*this).last_month = nullptr;
}
ListNode::ListNode(Record* record)
{
	// Initialize all variables
	// Linked List
	(*this).forward = nullptr;
	(*this).backward = nullptr;
	(*this).is_dummy = false;
	// Data
	(*this).record = record;
	(*this).dummy = nullptr;
	// Dummy
	(*this).length = 0;
	(*this).old = nullptr;
	(*this).last_week = nullptr;
	(*this).last_month = nullptr;
}
// destruct function of class ListNode
ListNode::~ListNode()
{
}

// ListNode::set variables
ListNode* ListNode::setForward(ListNode* forward)
{
	(*this).forward = forward;
	return this;
}
ListNode* ListNode::setBackward(ListNode* backward)
{
	(*this).backward = backward;
	return this;
}
ListNode* ListNode::setDummyBool(bool is_dummy)
{
	(*this).is_dummy = is_dummy;
	return this;
}
ListNode* ListNode::setRecord(Record* record)
{
	(*this).record = record;
	return this;
}
ListNode* ListNode::setDummyNode(ListNode* dummy)
{
	(*this).dummy = dummy;
	return this;
}
ListNode* ListNode::setLength(int length)
{
	(*this).length = length;
	return this;
}
ListNode* ListNode::setOld(ListNode* old)
{
	(*this).old = old;
	return this;
}
ListNode* ListNode::setLastMonth(ListNode* last_month)
{
	(*this).last_month = last_month;
	return this;
}
ListNode* ListNode::setLastWeek(ListNode* last_week)
{
	(*this).last_week = last_week;
	return this;
}

/*=================================*
 * Method: setRecordwithData
 * Created by CYTIN
 *----------------------------
 *   Generate record for node using
 * data from input string
 *==================================*/
ListNode* ListNode::setRecordwithData(string dataline, int reg_index, time_t current_time)
{
	string data[11] = {};
	{
		// split csv data
		int i = 0;
		int counter = 0;
		string tmp = "";
		int len = dataline.length();
		while (i < len) {
			if ('"' == dataline[i]) {
				// process data with quotation mark
				tmp = "";
				i++;
				while ('"' != dataline[i]) {
					tmp = tmp + dataline[i];
					i++;
				}
			}
			else if (',' == dataline[i]) {
				// split data when meeting comma or string end
				data[counter] = tmp;
				tmp = "";
				counter++;
			}
			else if ('\n' == dataline[i]) {
				// in case the string ends with \n
			}
			else {
				tmp = tmp + dataline[i];
			}
			i++;
		}
		// the last data has no comma
		data[counter] = tmp;
	}
	//cout << "ID:\t" << stoi(data[0]) << endl;
	// construct Record
	Record* record = new Record;
	(*record).setRecordID(stoi(data[0]) * reg_num + reg_index);
	(*record).setRecordName(data[1]);
	(*record).setRecordAddress(data[2]);
	(*record).setRecordPhone(data[3]);
	(*record).setRecordWeChat(data[4]);
	(*record).setRecordEmail(data[5]);
	//cout << data[7] << " | " << str2date(data[7]) << " |" << endl;
	(*record).setRecordBirth(str2date(data[7]), current_time);
	(*record).setRecordProfession(stoi(data[6]));
	(*record).setRecordRisk(stoi(data[8]));
	if ("TRUE" == capstr(data[9])) {
		(*record).setRecordDeadline(str2date(data[10]));
	}
	else {
		(*record).setRecordnoDeadline();
	}
	(*record).setRecordRegisterTime(current_time);
	(*record).setRecordRegistry(reg_index);
	(*this).record = record;

	return this;
}

/*=================================*
 * Method: ListNode::setDummy
 * Created by CYTIN
 *--------------------------
 * Set the node as a dummy node
 *==================================*/
ListNode* ListNode::setDummy()
{
	(*this).is_dummy = true;
	(*this).length = 0;
	(*this).record = nullptr;
	(*this).forward = this;
	(*this).backward = this;
	(*this).dummy = this;
	(*this).old = this;
	(*this).last_week = this;
	(*this).last_month = this;
	return this;
}

// ListNode::get variabl
ListNode* ListNode::getForward()
{
	return (*this).forward;
}
ListNode* ListNode::getBackward()
{
	return (*this).backward;
}
bool ListNode::getDummyBool()
{
	return (*this).is_dummy;
}
Record* ListNode::getRecord()
{
	return (*this).record;
}
ListNode* ListNode::getDummyNode()
{
	return (*this).dummy;
}
int ListNode::getLength()
{
	return (*this).length;
}
ListNode* ListNode::getOld()
{
	return (*this).old;
}
ListNode* ListNode::getLastMonth()
{
	return (*this).last_month;
}
ListNode* ListNode::getLastWeek()
{
	return (*this).last_week;
}

/*=================================*
 * Method: ListNode::remove
 * Created by CYTIN
 *--------------------------
 * Remove the node form its list
 *==================================*/
void ListNode::remove()
{
	if ((*this).is_dummy) {
		cerr << "Error: Removing dummy node" << endl;
		return;
	}
	(*(*this).dummy).length -= 1;
	if ((*(*this).dummy).old == this) {
		(*(*this).dummy).old = (*this).backward;
	}
	if ((*(*this).dummy).last_month == this) {
		(*(*this).dummy).last_month = (*this).backward;
	}
	if ((*(*this).dummy).last_week == this) {
		(*(*this).dummy).last_week = (*this).backward;
	}
	(*(*this).backward).forward = (*this).forward;
	(*(*this).forward).backward = (*this).backward;
	(*this).dummy = nullptr;
}

/*=================================*
 * Method: ListNode::remove
 * Created by CYTIN
 *--------------------------
 * Remove the node form the list
 *==================================*/
ListNode* ListNode::remove(ListNode* node)
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
 * Method: ListNode::append
 * Created by CYTIN
 *--------------------------
 *   Append the new node to the
 * end of list.
 *==================================*/
ListNode* ListNode::append(ListNode* new_node)
{
	if ((*new_node).is_dummy) {
		cerr << "error: cannot append a dummy node" << endl;
		return this;
	}
	// check if it is already in a list
	if (!((*new_node).dummy == nullptr)) {
		(*new_node).remove();
	}
	if ((*this).is_dummy) {
		(*new_node).dummy = this;
		(*new_node).forward = this;
		(*new_node).backward = (*this).backward;
		(*(*this).backward).forward = new_node;
		(*this).backward = new_node;
	}
	else {
		(*(*this).dummy).append(new_node);
	}
	return this;
}

/*=================================*
 * Method: ListNode::insert
 * Created by CYTIN
 *--------------------------
 * Add the new node after the node
 *==================================*/
ListNode* ListNode::insert(ListNode* new_node)
{
	if ((*new_node).is_dummy) {
		cerr << "Error: Cannot append a dummy node" << endl;
		return this;
	}
	// check if it is already in a list
	if (!((*new_node).dummy == nullptr)) {
		(*new_node).remove();
	}
	// Add the new node in the list
	{
		(*this).length += 1;
		(*new_node).forward = (*this).forward;
		(*new_node).backward = this;
		(*this).forward->backward = new_node;
		(*this).forward = new_node;
		(*new_node).dummy = (*this).dummy;
	}
}

/*=================================*
 * Method: ListNode::pop
 * Created by CYTIN
 *------------------------
 *   Remove the first node from the
 * list. Return its handle. Return
 * nullptr if the list is empty.
 *==================================*/
ListNode* ListNode::pop()
{
	ListNode* tmp = (*this).forward;
	if ((*tmp).is_dummy) {
		cout << "Warning: Poping from an empty list" << endl;
		return nullptr;
	}
	(*tmp).remove();
	return tmp;
}

/*=================================*
 * Method: ListNode::drop
 * Created by CYTIN
 *-------------------------
 *   Remove the last node from the
 * list. Return its handle. Return
 * nullptr if the list is empty.
 *==================================*/
ListNode* ListNode::drop()
{
	ListNode* tmp = (*this).backward;
	if ((*tmp).is_dummy) {
		cout << "Warning: Poping from an empty list" << endl;
		return nullptr;
	}
	(*tmp).remove();
	return tmp;
}

/*=================================*
 * Method: ListNode::find
 * Created by CYTIN
 *-------------------------
 *   Find node in list using index
 *==================================*/
ListNode* ListNode::find(int index)
{
	if (index >= (*(*this).dummy).length) {
		cerr << "Error: List index out of range" << endl;
		return nullptr;
	}
	ListNode* node = (*this).dummy;
	if (index >= 0) {
		for (int i = 0; i <= index; i++) {
			node = (*node).forward;
			if ((*node).is_dummy) {
				cerr << "Error: List index out of range" << endl;
				return nullptr;
			}
		}
	}
	else {
		for (int i = 0; i > index; i--) {
			node = (*node).backward;
			if ((*node).is_dummy) {
				cerr << "Error: List index out of range" << endl;
				return nullptr;
			}
		}
	}
	return node;
}

/*=================================*
 * Method: ListNode::shift
 * Created by CYTIN
 *--------------------------
 *   Find node using displacement
 * index with the given node
 *==================================*/
ListNode* ListNode::shift(int displace)
{
	ListNode* node = this;
	if (displace >= 0) {
		for (int i = 0; i <= displace; i++) {
			node = (*node).forward;
			if ((*node).is_dummy) {
				cerr << "Error: List index out of range" << endl;
				return nullptr;
			}
		}
	}
	else {
		for (int i = 0; i > displace; i--) {
			node = (*node).backward;
			if ((*node).is_dummy) {
				cerr << "Error: List index out of range" << endl;
				return nullptr;
			}
		}
	}
	return node;
}

/*=================================*
 * Method: ListNode::idsearch
 * Created by CYTIN
 *-----------------------------
 *   Find node using displacement
 * index with the given node
 *==================================*/
ListNode* ListNode::idsearch(int id)
{
	if ((*this).is_dummy) {
		ListNode* node = this;
		for (int i = 0; i < (*this).length; i++) {
			node = (*node).forward;
			if (id == (*(*node).record).getRecordID()) {
				return node;
			}
		}
		cout << "Node with given id was not found" << endl;
		return nullptr;
	}
	else {
		return (*(*this).dummy).idsearch(id);
	}
}

/*=================================*
 * Method: ListNode::copy
 * Created by CYTIN
 *-----------------------------
 * copy the node, with same record
 *==================================*/
ListNode* ListNode::copy()
{
	ListNode* new_node = new ListNode;
	(*new_node).forward = (*this).forward;
	(*new_node).backward = (*this).backward;
	(*new_node).is_dummy = (*this).is_dummy;
	(*new_node).record = (*this).record;
	(*new_node).dummy = (*this).dummy;
	(*new_node).length = (*this).length;
	(*new_node).old = (*this).old;
	(*new_node).last_month = (*this).last_month;
	(*new_node).last_week = (*this).last_week;
	return new_node;
}

/*=================================*
 * Method: ListNode::deepcopy
 * Created by CYTIN
 *-----------------------------
 * copy the node, with copied record
 *==================================*/
ListNode* ListNode::deepcopy()
{
	ListNode* new_node = (*this).copy();
	delete (*new_node).record;
	(*new_node).record = (*this).record->deepcopy();
	return new_node;
}

/*=====================================*
 * Method: ListNode::toFibNode
 * Created by FDChick
 *-----------------------------
 * transfer the ListNode to a FibNode
 *=====================================*/
FibNode* ListNode::toFibNode()
{
	FibNode* fibnode = new FibNode((*this).getRecord());
	return fibnode;
}

/*=================================*
 * Method: ListNode::recordInfo
 * Created by CYTIN
 *-----------------------------
 * copy the node, with copied record
 *==================================*/
string ListNode::recordInfo()
{
	string str;
	str = "| " + strjust(to_string((*this).record->getRecordID()), 6) + " | ";
	str = str + strjust((*this).record->getRecordName(), 20) + " | ";
	str = str + strjust((*this).record->getRecordPhone(), 16) + " | ";
	str = str + strjust((*this).record->getRecordWeChat(), 12) + " | ";
	str = str + strjust((*this).record->getRecordEmail(), 40) + " | ";
	str = str + strjust(to_string((*this).record->getRecordProfession()), 6) + " | ";
	time_t tmp = (*this).record->getRecordBirth();
	str = str + strjust(date_str(tmp), 16) + " | ";
	str = str + strjust(to_string((*this).record->getRecordRisk()), 6) + " | ";
	if ((*this).record->getRecordDDLBool()) {
		tmp = (*this).record->getRecordDeadline();
		str = str + strjust(date_str(tmp), 16) + " | ";
	}
	else {
		str = str + strjust(" ", 16) + " | ";
	}
	str = str + strjust((*this).record->getRecordAddress(), 32) + " |";
	return str;
}