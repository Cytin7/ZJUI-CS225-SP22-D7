#include "FibNode.h"

// construct functon of class ListNode
FibNode::FibNode()
{
	// Initialize all variables
	(*this).left = this;
	(*this).right = this;
	(*this).parent = nullptr;
	(*this).child = nullptr;
	(*this).degree = 0;
	(*this).mark = false;
	// data
	Record* empty_record = new Record;
	(*this).record = empty_record;
}

FibNode::FibNode(Record* record)
{
	// Initialize all variables
	(*this).left = this;
	(*this).right = this;
	(*this).parent = nullptr;
	(*this).child = nullptr;
	(*this).degree = 0;
	(*this).mark = false;
	// data
	(*this).record = record;
}

FibNode::~FibNode()
{
}

// set Record data by each variable
void FibNode::setLeft(FibNode* left)
{
	(*this).left = left;
	return;
}
void FibNode::setRight(FibNode* right)
{
	(*this).right = right;
	return;

}
void FibNode::setParent(FibNode* parent)
{

	(*this).parent = parent;
	return;
}
void FibNode::setChild(FibNode* child)
{
	(*this).child = child;
	return;
}
void FibNode::setDegree(int degree)
{
	(*this).degree = degree;
	return;
}
void FibNode::setMark(bool mark)
{
	(*this).mark = mark;
	return;
}
void FibNode::setRecord(Record* record)
{
	(*this).record = record;
	return;
}

// get Record data by each variable
FibNode* FibNode::getLeft()
{
	return (*this).left;
}
FibNode* FibNode::getRight()
{
	return (*this).right;
}
FibNode* FibNode::getParent()
{
	return (*this).parent;
}
FibNode* FibNode::getChild()
{
	return (*this).child;
}
int FibNode::getDegree()
{
	return (*this).degree;
}
bool FibNode::getMark()
{
	return (*this).mark;
}
Record* FibNode::getRecord()
{
	return (*this).record;
}


/*=================================*
 * Method: FibNode::append
 * Created by FDChick
 *-----------------------------
 *   Add a new node after the node
 *==================================*/
void FibNode::append(FibNode* node)
{
	(*node).left = this;
	(*node).right = (*this).right;
	(*(*this).right).left = node;
	(*this).right = node;
	return;
}

/*=================================*
 * Method: FibNode::addChild
 * Created by FDChick
 *-----------------------------
 *   Set another tree as one child
 * of this tree.
 *==================================*/
void FibNode::addChild(FibNode* root)
{
	if (nullptr != (*root).parent) {
		cout << "Warn: the node might be a child of an existing tree." << endl;
	}
	if ((*this).degree != (*root).degree) {
		cout << "Warn: setting a tree of different degree as new child." << endl;
	}
	// adding root to children list
	(*root).parent = this;
	(*this).degree += 1;
	if (nullptr == (*this).child) {
		(*this).child = root;
		(*root).left = root;
		(*root).right = root;
	}
	else {
		(*(*this).child).append(root);
		//(*root).right = (*this).child;
		//(*root).left = (*(*this).child).left;
		//(*(*(*this).child).left).right = root;
		//(*(*this).child).left = root;
	}
	return;
}

/*=================================*
 * Method: FibNode::concat
 * Created by FDChick
 *-----------------------------
 *   Concat roots of another heap.
 *==================================*/
void FibNode::concat(FibNode* root)
{
	FibNode* A = (*this).right;
	FibNode* B = (*root).right;

	(*this).right = B;
	(*B).left = this;
	(*root).right = A;
	(*A).left = root;
}

/*=================================*
 * Method: FibNode::removeTree
 * Created by FDChick
 *-----------------------------
 * Remove the tree from the heap.
 *-----------------------------
 *   Be careful. Check if the root
 * of the tree is the min root. If
 * so, exicute reset_min
 *==================================*/
 //void FibNode::removeTree(FibNode* root)
 //{
 //	if (nullptr != (*root).parent) {
 //		cerr << "Error: romoving a node which is not a root of a tree." << endl;
 //	}
 //
 //}

 /*=================================*
  * Method: FibNode::idsearch
  * Created by FDChick
  *-----------------------------
  *   Use recursion to search a node
  * with given id. If not found
  * return nullptr
  *==================================*/
FibNode* FibNode::idsearch(int id)
{
	if (id == (*(*this).getRecord()).getRecordID()) {
		cout << "\t找到了！是" << this << endl;
		return this;
	}

	if (nullptr == (*this).getChild()) {
		return nullptr;
	}
	FibNode* result = (*(*this).child).idsearch(id);
	FibNode* node = (*(*this).child).right;
	while ((nullptr == result) && (node != (*this).child)) {
		result = (*node).idsearch(id);
		if (!(nullptr == result)) {
			return result;
		}
		node = (*node).getRight();
	}
	return result;
}

/*=================================*
 * Method: FibNode::updateDegree
 * Created by Peidong Yang
 *-----------------------------
 *   Update the degree of the node
 * when heap shape has changed.
 *==================================*/
int FibNode::updateDegree()
{
	if (nullptr == (*this).child) {
		cout << "\t\t\t发生什么事了SAAA" << endl;
		(*this).degree = 0;
	}
	else {
		cout << "\t\t\t发生什么事了AAAA" << endl;
		(*(*this).child).updateDegree();
		int counter = 1;
		FibNode* node = (*(*this).child).right;
		while (node != (*this).child) {
			cout << "\t\t\t发生什么事了BAAA" << endl;
			(*node).updateDegree();
			counter++;
			node = (*node).right;
		}
		(*this).degree = counter;
	}
	return (*this).degree;
}

/*=================================*
 * Method: FibNode::copy
 * Created by FDChick
 *-----------------------------
 *   Copy the Fibnode and get a new
 * Fibnode with same record pointer
 *==================================*/
FibNode* FibNode::copy()
{
	FibNode* new_ptr = new FibNode((*this).record);
	return new_ptr;
}

