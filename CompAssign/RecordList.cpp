#include "CompAssign.h"


RecordList::RecordList()
{
	this->length = 0;
	this->setForward(this);
	this->setBackward(this);
}

RecordList::~RecordList()
{
}

int RecordList::getLength() const
{
	return this->length;
}
//RecordNode* RecordList::getDummy() const
//{
//	return this;
//}

RecordList* RecordList::setLength(int length)
{
	this->length = length;
	return this;
}

RecordList* RecordList::deepcopy() const
{
	RecordList new_list;
	RecordNode* node = this->getForward();
	while (!node->is_dummy())
	{
		new_list.append(node->deepcopy());
	}
	return &new_list;
}

void RecordList::printRecords() const
{
	RecordNode* node = this->forward;
	for (int i = this->getLength(); i > 0; i--)
	{
		node->printRecord();
		node = node->getForward();
	}
}

// Add the new node to the end of the list
RecordNode* RecordList::append(RecordNode* new_node)
{
	new_node->setBackward(this->getBackward());
	new_node->setForward(this);
	this->getBackward()->setForward(new_node);
	this->setBackward(new_node);
	this->length += 1;
	return new_node;
}

// Find the node of index k;
RecordNode* RecordList::get(int k) const
{
	if (k > this->getLength())
	{
		cout << "Error: get(k) index out of range" << endl;
		return NULL;
	}
	RecordNode* node = this->getForward();
	for (int i = k; i > 0; i--)
	{
		if (node->is_dummy())
		{
			cout << "Error: get(k) index out of range" << endl;
			return NULL;
		}
		node = node->getForward();
	}
	return node;
}

// insert the new node between node k and node k+1
RecordNode* RecordList::insert(RecordNode* insert_node, int k)
{
	if (k > this->getLength())
	{
		cout << "Error: insert(node,k) index out of range" << endl;
		return NULL;
	}
	RecordNode* node = this;
	for (int i = k; i > 0; i--)
	{
		node = node->getForward();
		if (node->is_dummy())
		{
			cout << "Error: insert(node,k) index out of range" << endl;
			return NULL;
		}
	}
	node->getForward()->setBackward(insert_node);
	insert_node->setForward(node->getForward());
	insert_node->setBackward(node);
	node->setForward(insert_node);
	this->length += 1;
	return insert_node;
}

// take away the node from the list, but node delete it.
RecordNode* RecordList::take_away(RecordNode* node)
{
	node->getForward()->setBackward(node->getBackward());
	node->getBackward()->setForward(node->getForward());
	this->length -= 1;
	return node;
}

void RecordList::delete_node(RecordNode* node)
{
	this->take_away(node);
	delete[] node;
}

// contact of two list
RecordList* RecordList::operator*(RecordList* list2)
{
	RecordList sum_list;
	RecordNode* node = this;
	for (int i = this->length; i > 0; i--)
	{
		node = node->getForward();
		if (node->is_dummy())
		{
			cout << "Error: List length larger than real length" << endl;
			return NULL;
		}
		sum_list.append(node);
	}
	node = list2;
	for (int i = list2->length; i > 0; i--)
	{
		node = node->getForward();
		if (node->is_dummy())
		{
			cout << "Error: List length larger than real length" << endl;
			return NULL;
		}
		sum_list.append(node);
	}
	return &sum_list;
}

// extend another list to this list
RecordList* RecordList::extend(RecordList* list2)
{
	RecordNode* node = list2;
	for (int i = list2->length; i > 0; i--)
	{
		node = node->getForward();
		if (node->is_dummy())
		{
			cout << "Error: List length larger than real length" << endl;
			return NULL;
		}
		this->append(node);
	}
	return this;
}

// find the node of index k
RecordNode* RecordList::operator[](int k) const
{
	return this->get(k);
}

// append new node to the end of the list
RecordList* RecordList::operator+(RecordNode* new_node)
{
	this->append(new_node);
	return this;
}