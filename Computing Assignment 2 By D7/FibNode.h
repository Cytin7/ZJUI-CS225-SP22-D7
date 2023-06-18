#pragma once
#include "Record.h"

/*=================================*
 * Class: FibNode
 * Created by FDChick
 *---------------------
 * Node of Fibonacci Heap
 * Used for priority queue
 *==================================*/
class FibNode
{
public:
	// Variables
	FibNode* left;		// pointer to right sibling
	FibNode* right;		// pointer to right sibling
	FibNode* parent;	// pointer to parent node
	FibNode* child;		// pointer to one of the children node
	int degree;			// number of children nodes
	bool mark;		    // Marked if one of the children is deleted
	Record* record;		// Record data
    int key;
    int type;

public:
	// Construct and destruct functions
	FibNode(int type, Record* record);
	~FibNode();

public:
    void setType(int type);
	// set Record data by each variable
	void setLeft(FibNode* left);
	void setRight(FibNode* right);
	void setParent(FibNode* parent);
	void setChild(FibNode* child);
	void setDegree(int degree);
	void setMark(bool mark);
	void setRecord(Record* record);
	// get Record data by each variable
	FibNode* getLeft();
	FibNode* getRight();
	FibNode* getParent();
	FibNode* getChild();
	int getDegree();
	bool getMark();
	Record* getRecord();
    void calcKey();
    int getKey();

public:
	// Fibnode operations
	void append(FibNode* node);
	void addChild(FibNode* root);
	void concat(FibNode* root);
	//void removeTree(FibNode* root);
	FibNode* idsearch(int id);
	int updateDegree();
	// FibNode<T>* copy();
	// ListNode* toListNode();
};

#include "time.h"

// construct functon of class ListNode
FibNode::FibNode(int type, Record* record)
{
    // Initialize all variables
    (*this).type = type;
    (*this).left = this;
    (*this).right = this;
    (*this).parent = nullptr;
    (*this).child = nullptr;
    (*this).degree = 0;
    (*this).mark = false;
    (*this).record = record;
    calcKey();
    return;
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
 * Method: FibNode::updateDegree
 * Created by Peidong Yang
 *-----------------------------
 *   Update the degree of the node
 * when heap shape has changed.
 *==================================*/

int FibNode::updateDegree()
{
    if (nullptr == (*this).child) {
        (*this).degree = 0;
    }
    else {
        int counter = 1;
        FibNode* node = (*(*this).child).right;
        while (node != (*this).child) {
            (*node).updateDegree();
            counter++;
            node = (*node).right;
        }
        (*this).degree = counter;
        (*(*this).child).updateDegree();
    }
    return (*this).degree;
}

/*================================*
 * Method: FibNote::getKey();
 * Created by FDChick
 *-----------------------------
 *  to calculate different key value
 *  for the sort of the FibHeap.
 *
 *================================*/
void FibNode::calcKey(){
    if (((*this).type == 1) && ((*this).type == 3)){
        // type 1 is main heap.
        // and the key type is only int.
        Record* rcd = (*this).record;
        time_t reg =  (*rcd).getRecordRegisterTime();
        tm regtm = *localtime(&reg);
        int yr = (regtm).tm_year - 2000;
        // year will occupy 2 bits of the key.
        int dy = (regtm).tm_yday;
        // day will occupy 3 bits of the key.
        int ag = (*rcd).getRecordAgeGroup();
        // ag group will occupy 1 bit.
        int prof = (*rcd).getRecordProfession();
        // prof will occupy 1 bit.
        (*this).key = dy + 1000*yr + 100000*ag + 1000000*prof;
        return;
    }else if ((*this).type == 2){
        // type 2 stands for the deadline heap.
        Record* rcd = (*this).record;
        time_t ddl =  (*rcd).getRecordDeadline();
        tm ddltm = *localtime(&ddl);
        int yr = (ddltm).tm_year;
        int dy = (ddltm).tm_yday;
        (*this).key = dy + 1000*yr;
        return;
    }
}

int FibNode::getKey() {
    return key;
}

void FibNode::setType(int type) {
    (*this).type = type;
    return;
}
