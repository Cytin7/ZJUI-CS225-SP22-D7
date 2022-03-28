#include "CompAssign.h"

// construct function
DNode::DNode()
{
	this->forward = NULL;
	this->backward = NULL;
}

// destruct function
DNode::~DNode()
{
	if (this->forward != NULL && this->forward->backward == this)
	{
		this->forward->backward = this->backward;
	}
	if (this->backward != NULL && this->backward->forward == this)
	{
		this->backward->forward = this->forward;
	}
}

// set forward and backward pointer
DNode* DNode::setForward(DNode* forward)
{
	this->forward = forward;
	return this;
}
DNode* DNode::setBackward(DNode* backward)
{
	this->backward = backward;
	return this;
}
// set forward and backward pointer
DNode* DNode::getForward()
{
	return this->forward;
}
DNode* DNode::getBackward()
{
	return this->backward;
}

DNode* DNode::deepcopy()
{
	DNode new_node;
	new_node.backward = this->backward;
	new_node.forward = this->forward;
	return &new_node;
}