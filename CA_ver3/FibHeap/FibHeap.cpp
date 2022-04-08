#include "FibHeap.h"

//
// Created by FDChick on 2022/4/4.
//

/*
 *
 * Created By FDChick on 2022/4/5
 * Here Are the functions to define
 * All the methods in the class
 * FibHeap
 *
 */
FibHeap::FibHeap() {
	this->numitems = 0;
	this->maxDegree = 0;
	this->min = NULL;
	this->cons = NULL;
}
FibHeap::~FibHeap() {
	cout << "one of the FibHeap is leaving us forever.\n";
}
// 移除某个节点出双链表
void FibHeap::removeNode(FibNode* node) {
	node->getRightSib()->setLeftSib(node->getLeftSib());
	node->getLeftSib()->setRightSib(node->getRightSib());
	return;
}
//
// This function called
// Add_Node used
// for add nodes to siblings
//
void FibHeap::Add_Node(FibNode* node, FibNode* root) {
	FibNode* ptr = root->getRightSib();
	ptr->setLeftSib(node);
	node->setLeftSib(root);
	return;
}
//
// This function called
// Insert used
// for add nodes to siblings
//
void FibHeap::Insert(FibNode* node) {
	if (numitems == 0) {
		min = node;
	}
	else {
		Add_Node(node, min);
		if (node->get_priority_number() < min->get_priority_number()) {
			min = node;
		}
	}
	numitems++;
	return;
}

// Remove The minimum value node of this heap.
void FibHeap::removeMin() {
	if (min == NULL) {
		return;
	}
	FibNode* child = NULL;
	FibNode* m = min;
	// To merge all the children to the root list.
	while (m->getChild() != NULL) {
		m->setChild(child);
		removeNode(child);
		if (child->getRightSib() == child) {
			m->setChild(NULL);
		}
		else {
			m->setChild(child->getRightSib());
		}
		Add_Node(child, min);
		child->setParent(NULL);
	}
	// remove node m out of the root list.
	removeNode(m);
	// if m is the only node in the heap, then set min to be NULL.
	// Otherwise set the min node
	// to be one of the non-empty node (m->right)
	// then modify the heap.
	if (m->getRightSib() == m) {
		min = NULL;
	}
	else {
		min = m->getRightSib();
		Consolidate();
	}
	numitems--;
	delete m;
	return;
}

/// Update the node's location to maintain the heap's character.
// the former key value is temp.
void FibHeap::update(FibNode* node, int temp) {
	if (min == NULL || node == NULL) {
		return;
	}
	int key = node->get_priority_number();
	if (key < temp) {
		decrease(node, key);
	}
	else if (key > temp) {
		increase(node, key);
	}
	else {
		cout << "Update Error: No need to update." << endl;
	}
}

// Print out to display the FibHeap.
void FibHeap::print() {
	int i = 0;
	FibNode* p;
	if (min == NULL) {
		return;
	}
	cout << "== Detailed Infos of FibHeap: ==" << endl;
	p = min;
	do {
		i++;
		//cout << setw(2) << i << ". " << setw(4) << p->get_priority_number() << "(" << p->getdegree() << ") is root" << endl;
		cout << i << ". " << p->get_priority_number() << "(" << p->getdegree() << ") is root" << endl;
		print(p->getChild(), p, 1);
		p = p->getRightSib();
	} while (p != min);
	cout << endl;
	return;
}
//// Destroy the FibHeap.
//void FibHeap::destroy() {
//	destroyNode(min);
//	free(cons);
//}


// Operation to pop out the min node.
// Directly to connect the min-node's sub-tree in to root list.
// concat all the trees that has the same degree until
// there is no trees have the same degree.
FibNode* FibHeap::Pop_Min() {
	FibNode* p = min;
	if (p == p->getRightSib()) {
		min = NULL;
	}
	else {
		removeMin();
	}
	p->setLeftSib(p);
	p->setRightSib(p);
	return p;
}
FibNode* FibHeap::extractMin()
{
	FibNode* p = min;

	if (p == p->getRightSib())
		min = NULL;
	else
	{
		removeNode(p);
		min = p->getRightSib();
	}
	p->setLeftSib(p);
	p->setLeftSib(p);
	return p;
}

/*
 * These Three are the operation to
 * consolidate the trees that have
 * the same degrees.
 */
void FibHeap::link_Node(FibNode* node, FibNode* root) {
	// remove the node in the double linked list.
	removeNode(node);
	// set the root's child.
	if (root->getChild() == NULL) {
		root->setChild(node);
	}
	else {
		Add_Node(node, root->getChild());
	}
	node->setParent(root);
	root->degree++;
	node->mark_status = false;
	return;
}
// renew the degree.
void FibHeap::renewDegree(FibNode* parent, int degree) {
	parent->degree -= degree;
	if (parent->getParent() != NULL) {
		renewDegree(parent->getParent(), degree);
	}
	return;
}
void FibHeap::Cons_Make() {
	int prev = maxDegree;
	maxDegree = (log(numitems) / log(2.0)) + 1;
	if (prev >= maxDegree) {
		return;
	}
	cons = (FibNode**)realloc(cons, sizeof(FibHeap*) * (maxDegree + 1));
	return;
}
void FibHeap::Consolidate() {
	int i, d, D;
	FibNode* x, * y, * tmp;
	Cons_Make();
	D = maxDegree + 1;
	for (i = 0; i < D; i++) {
		cons[i] = NULL;
	}
	while (min != NULL) {
		x = Pop_Min();                // 取出堆中的最小树(最小节点所在的树)
		d = x->degree;                    // 获取最小树的度数
		// cons[d] != NULL，意味着有两棵树(x和y)的"度数"相同。
		while (cons[d] != NULL) {
			y = cons[d];                // y是"与x的度数相同的树"
			if (x->get_priority_number() > y->get_priority_number()) {
				FibNode* temp;
				temp = x;
				x = y;
				y = temp;
			}
			link_Node(y, x);    // 将y链接到x中
			cons[d] = NULL;
			d++;
		}
		cons[d] = x;
	}
	min = NULL;
	// 将cons中的结点重新加到根表中
	for (i = 0; i < D; i++) {
		if (cons[i] != NULL) {
			if (min == NULL) {
				min = cons[i];
			}
			else {
				Add_Node(cons[i], min);
				if ((cons[i])->get_priority_number() < min->get_priority_number()) {
					min = cons[i];
				}
			}
		}
	}
	return;
}
// 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
void FibHeap::cut(FibNode* node, FibNode* parent) {
	removeNode(node);
	renewDegree(parent, node->degree);
	// node没有兄弟
	if (node == node->getRightSib()) {
		parent->setChild(NULL);
	}
	else {
		parent->setChild(node->getRightSib());
	}
	node->setParent(NULL);
	node->setLeftSib(node);
	node->setRightSib(node);
	node->mark_status = false;
	// 将"node所在树"添加到"根链表"中
	Add_Node(node, min);
	return;
}
// 对节点node进行"级联剪切"
void FibHeap::cascadingCut(FibNode* node) {
	FibNode* parent = node->getParent();
	if (parent != NULL) {
		if (node->mark_status == false) {
			node->mark_status = true;
		}
		else {
			cut(node, parent);
			cascadingCut(parent);
		}
	}
	return;
}
// 将斐波那契堆中节点node的值减少为key
void FibHeap::decrease(FibNode* node, int key) {
	FibNode* parent = node->getParent();
	if (parent != NULL && key < parent->get_priority_number()) {
		// 将node从父节点parent中剥离出来，并将node添加到根链表中
		cut(node, parent);
		cascadingCut(parent);
	}
	if (key < min->get_priority_number()) {
		min = node;
	}
	return;
}
// 将斐波那契堆中节点node的值增加为key
void FibHeap::increase(FibNode* node, int key) {
	FibNode* child, * parent, * right;
	// 将node每一个儿子(不包括孙子,重孙,...)都添加到"斐波那契堆的根链表"中
	while (node->getChild() != NULL) {
		child = node->getChild();
		removeNode(child);
		if (child->getRightSib() == child) {
			node->setChild(NULL);
		}
		else {
			node->setChild(child->getRightSib());
		}
		Add_Node(child, min);       // 将child添加到根链表中
		child->setParent(NULL);
	}
	node->degree = 0;
	// 如果node不在根链表中，
	//     则将node从父节点parent的子链接中剥离出来，
	//     并使node成为"堆的根链表"中的一员，
	//     然后进行"级联剪切"
	// 否则，则判断是否需要更新堆的最小节点
	parent = node->getParent();
	if (parent != NULL) {
		cut(node, parent);
		cascadingCut(parent);
	}
	else if (min == node) {
		right = node->getRightSib();
		while (right != node) {
			if (key > right->get_priority_number()) {
				min = right;
			}
			right = right->getRightSib();
		}
	}
	return;
}

// Search a node which has a ID.
FibNode* FibHeap::idsearch(FibNode* root, int id) {
	FibNode* t = root;
	FibNode* p = NULL;
	if (root == NULL) {
		return root;
	}
	do {
		if (t->getRecordID() == id) {
			p = t;
			break;
		}
		else {
			if ((p = idsearch(t->getChild(), id)) != NULL) {
				break;
			}
		}
		t = t->getRightSib();
	} while (t != root);
	return p;
}

FibNode* FibHeap::getMin() {
	return this->min;
}

// 删除结点node
void FibHeap::remove(FibNode* node) {
	int temp = node->get_priority_number();
	node->priority_change();
	update(node, temp);
	removeMin();
	node->set_priority_number(temp);
	return;
}
// 销毁斐波那契堆
/*
void FibHeap::destroyNode(FibNode *node){
	FibNode* start = node;
	if(node == NULL){
		return;
	}
	do {
		destroyNode(node->getChild());
		// 销毁node，并将node指向下一个
		node = node->getRightSib();
		delete node->getLeftSib();
	} while(node != start);
	return;
}
*/
// 打印斐波那契堆
void FibHeap::print(FibNode* node, FibNode* prev, int direction) {
	FibNode* start = node;
	if (node == NULL)
		return;
	do {
		if (direction == 1) {
			cout << node->get_priority_number() << "the degree is (" << node->degree << ") is " << prev->get_priority_number() << "'s child" << endl;
		}
		else {
			cout << node->get_priority_number() << "the degree is (" << node->degree << ") is " << prev->get_priority_number() << "'s next" << endl;
		}
		if (node->getChild() != NULL) {
			print(node->getChild(), node, 1);
		}
		// 兄弟节点
		prev = node;
		node = node->getRightSib();
		direction = 2;
	} while (node != start);
	return;
}

// Loop through the whole heap and minus 1;
void FibHeap::LoopMinus(FibNode* ptr) {
	FibNode* t = ptr;
	if (ptr == NULL) {
		return;
	}
	else {
		do {
			t->MinusOne();
			LoopMinus(t->getChild());
			t = t->getRightSib();
		} while (t != ptr);
		return;
	}
}

// Minus 1 function in the FibNode Class.
void FibNode::MinusOne() {
	this->priority_number--;
	return;
}