#include "CompAssign.h"

// construct node as dummy node
RecordNode::RecordNode()
{
	this->dummy_bool = true;
	this->forward = this;
	this->backward = this;
}
// construct node with input value
RecordNode::RecordNode(unsigned int id,
	string name = "",
	string address = "",
	string phone = "",
	string WeChat = "",
	string email = "",
	int prof = 1,
	time_t birth = (time_t)0,
	int risk = 0,
	time_t time_stamp = NULL) :Record(id, name, address, phone, WeChat, email, prof, birth, risk, time_stamp) 
{
	this->dummy_bool = false;
};

RecordNode::~RecordNode()
{
}

RecordNode* RecordNode::deepcopy() const
{
	RecordNode new_node(id, name, address, phone, WeChat, email, profession, birth, risk, time_stamp);
	new_node.backward = this->backward;
	new_node.forward = this->forward;
	return &new_node;
}

RecordNode* RecordNode::setForward(RecordNode* forward)
{
	this->forward = forward;
	return this->forward;
}
RecordNode* RecordNode::setBackward(RecordNode* backward)
{
	this->backward = backward;
	return this->backward;
}
RecordNode* RecordNode::getForward() const
{
	return this->forward;
}
RecordNode* RecordNode::getBackward() const
{
	return this->backward;
}
bool RecordNode::is_dummy() const
{
	return this->dummy_bool;
}