#include "../head.h"

PNode<class T>::PNode()
{
	dummy = NULL;
	forward = NULL;
	backward = NULL;
	is_dummy = false;
	length = 0;
	pointer = NULL;

}

PNode<class T>::~PNode()
{
}

void PNode<class T>::set_dummy()
{
	is_dummy = true;
	length = 0;
	forward = this;
	backward = this;
	dummy = this;
	pointer = NULL;
}

void PNode<class T>::set_member(T* handle)
{
	is_dummy = false;
	length = 0;
	forward = NULL;
	backward = NULL;
	dummy = NULL;
	pointer = handle;
}


void PNode<class T>::append(T* handle)
{
	PNode new_node;
	new_node.set_member(handle);
	new_node.dummy = this;
	new_node.backward = this->backward;
	new_node.forward = this;
	this->backward->forward = &new_node;
	this->backward = &new_node;
	this->length = this->length + 1;

}

void PNode<class T>::deleteNode()
{
	this->dummy->length = this->dummy->length - 1;
	this->backward->forward = this->forward;
	this->forward->backward = this->backward;
	delete[] this;
}