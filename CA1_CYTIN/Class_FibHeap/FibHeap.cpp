#include "FibHeap.h"

// construct functon of class ListNode
FibHeap::FibHeap()
{
	(*this).numitems = 0;
	(*this).maxDegree = 0;
	(*this).min = NULL;
}

FibHeap::~FibHeap()
{
}

// return variables
int FibHeap::getNumitems()
{
	return (*this).numitems;
}
int FibHeap::getMaxDegree()
{
	return (*this).maxDegree;
}
FibNode* FibHeap::getMin()
{
	return (*this).min;
}

/*=================================*
 * Method: FibHeap::insert
 * Created by FDChick
 *-----------------------------
 * insert a new node into hte list
 *==================================*/
void FibHeap::insert(FibNode* node, bool fc(FibNode*, FibNode*))
{
	if (0 == (*this).numitems) {
		(*this).min = node;
		(*this).numitems += 1;
	}
	else {
		(*(*this).min).append(node);
		(*this).numitems += 1;
		//cout << "\t\t添加节点" << endl;
		if (fc(node, (*this).min)) {
			(*this).min = node;
		}
		//cout << "\t\t目前节点数：" << (*this).numitems << endl;
		(*this).consolidate(fc);
	}
	return;
}

/*=================================*
 * Method: FibHeap::combine
 * Created by FDChick
 *-----------------------------
 *   Combine another Fibonacci heap
 * into this one.
 *==================================*/
void FibHeap::combine(FibHeap* heap, bool fc(FibNode*, FibNode*))
{
	if (NULL == heap || 0 == (*heap).numitems) {
		return;
	}
	if (0 == (*this).numitems) {
		(*this).numitems = (*heap).numitems;
		(*this).maxDegree = (*heap).maxDegree;
		(*this).min = (*heap).min;
		delete heap;
		return;
	}
	(*(*this).min).concat((*heap).min);
	if (fc((*heap).min, (*this).min)) {
		(*this).min = (*heap).min;
	}
	(*this).numitems += (*heap).numitems;
	delete heap;
	(*this).consolidate(fc);
	return;
}

/*=================================*
 * Method: FibHeap::reset_min
 * Created by FDChick
 *-----------------------------
 * Check all tree root and find min
 *==================================*/
void FibHeap::reset_min(bool fc(FibNode*, FibNode*))
{
	FibNode* min = (*this).min;
	FibNode* node = (*min).getRight();
	while (node != (*this).min) {
		if (fc(node, min)) {
			min = node;
		}
		node = (*node).getRight();
	}
	(*this).min = min;
	return;
}

/*=====================================*
 * Method: FibHeap::remove_min_tree
 * Created by FDChick
 *-----------------------------
 * Removing the tree with min root.
 * The operation will not delete it.
 *======================================*/
FibNode* FibHeap::remove_min_tree(bool fc(FibNode*, FibNode*))
{
	if (NULL == (*this).min) {
		cout << "Error: the heap is already empty." << endl;
		return NULL;
	}
	FibNode* min_node = (*this).min;
	if (min_node == (*min_node).getRight()) {
		(*this).min = NULL;
	}
	else {
		(*this).min = (*min_node).getRight();
		// setlink
		(*(*min_node).getLeft()).setRight((*min_node).getRight());
		(*(*min_node).getRight()).setLeft((*min_node).getLeft());
		// maintain H.min
		(*this).reset_min(fc);
	}
	(*min_node).setLeft(min_node);
	(*min_node).setRight(min_node);
	return min_node;
}

/*=================================*
 * Method: FibHeap::consolidate
 * Created by FDChick
 *-----------------------------
 *   Combining trees with same
 * degree until all degrees of
 * trees are different.
 *==================================*/
void FibHeap::consolidate(bool fc(FibNode*, FibNode*))
{
	cout << "\t\t发生什么事了A" << endl;
	if (NULL == (*this).min || 0 == (*this).numitems) {
		return;
	}
	cout << "\t\t发生什么事了B" << endl;
	// re- calculate degree for all nodes
	FibNode* nodeptr = (*(*this).min).getRight();
	cout << "\t\t发生什么事了C" << endl;
	while (nodeptr != (*this).min) {
		(*nodeptr).updateDegree();
		nodeptr = (*nodeptr).getRight();
	}
	cout << "\t\t发生什么事了D" << endl;
	// create array arr for consolidate
	int Deg = (int)log2((*this).numitems) + 2;
	FibNode** arr = (FibNode**)calloc(Deg, sizeof(FibNode*));
	for (int i = 0; i < Deg; i++) {
		arr[i] = NULL;
	}
	FibNode* a, * b;
	int d;
	cout << "\t\t发生什么事了E" << endl;
	// remove min_tree and murge
	while (NULL != (*this).min) {
		a = this->remove_min_tree(fc);
		d = (*a).getDegree();
		while (!(arr[d] == NULL)) {
			b = arr[d];
			if (fc(a, b)) {
				(*a).addChild(b);
			}
			else {
				(*b).addChild(a);
				a = b;
			}
			arr[d] = NULL;
			d++;
		}
		arr[d] = a;
	}
	// concat back the nodes.
	cout << "\t\t发生什么事了F" << endl;
	for (int i = 0; i < Deg; i++) {
		if (arr[i] != NULL) {
			if (NULL == (*this).min) {
				(*this).min = arr[i];
			}
			else {
				(*(*this).min).append(arr[i]);
				if (fc(arr[i], (*this).min)) {
					(*this).min = arr[i];
				}
			}
		}
	}
	cout << "\t\t发生什么事了G" << endl;
	// re- calculate degree for all nodes
	FibNode* node = (*(*this).min).getRight();
	int max = (*(*this).min).updateDegree();
	int tmp;
	//system("pause");
	while (node != (*this).min) {
		tmp = (*node).updateDegree();
		cout << "\t\t============" << endl;
		if (max < tmp) {
			max = tmp;
		}
		node = (*node).getRight();
	}
	(*this).maxDegree = max;
	free(arr);
}


/*=================================*
 * Method: FibHeap::pop_min
 * Created by FDChick
 *-----------------------------
 *   Remove the min node from the
 * Fibonacci heap.
 *==================================*/
FibNode* FibHeap::pop_min(bool fc(FibNode*, FibNode*))
{
	if (NULL == this || 0 == (*this).numitems) {
		return NULL;
	}
	// set all min's children's parent to NULL
	(*(*this).min).setParent(NULL);
	(*(*(*this).min).getChild()).setParent(NULL);
	FibNode* node = (*(*(*this).min).getChild()).getRight();
	while (node != (*(*this).min).getChild()) {
		(*node).setParent(NULL);
		node = (*node).getRight();
	}
	(*(*this).min).concat((*(*this).min).getChild());
	// remove the min node
	node = (*this).min;
	if (node == (*node).getRight()) {
		(*this).min = NULL;
	}
	else {
		(*this).min = (*node).getRight();
		(*(*node).getLeft()).setRight((*node).getRight());
		(*(*node).getRight()).setLeft((*node).getLeft());
		(*this).reset_min(fc);
		(*this).consolidate(fc);
	}
	(*this).numitems -= 1;
	(*node).setParent(NULL);
	(*node).setChild(NULL);
	(*node).setLeft(NULL);
	(*node).setRight(NULL);
	return node;
}

/*=================================*
 * Method: FibHeap::update
 * Created by FDChick
 *-----------------------------
 *   When the information of a node
 * has been updated, the priority
 * of the Fibonacci heap will need
 * an update.
 *==================================*/
void FibHeap::update(int id, bool fc(FibNode*, FibNode*))
{
	FibNode* node = (*(*this).min).idsearch(id);
	if (NULL == node) {
		return;
	}
	// Check the influence of the update
	if (fc((*node).getParent(), node)) {
		// If priority down
		(*(*node).getChild()).setParent(NULL);
		FibNode* tmp = (*(*node).getChild()).getRight();
		while (tmp != (*node).getChild()) {
			(*tmp).setParent(NULL);
			tmp = (*tmp).getRight();
		}
		(*(*this).min).concat((*node).getChild());
		(*node).setChild(NULL);
	}

	FibNode* tmp = (*node).getParent();
	while (NULL != tmp) {
		(*node).setMark(false);
		if (node == (*node).getRight()) {
			(*tmp).setChild(NULL);
		}
		else {
			(*tmp).setChild((*node).getRight());
			// remove the node from sibling list
			(*(*node).getLeft()).setRight((*node).getRight());
			(*(*node).getRight()).setLeft((*node).getLeft());
		}

		(*node).setParent(NULL);
		(*node).setLeft(NULL);
		(*node).setRight(NULL);
		// append the node to the roots
		(*(*this).min).append(node);

		// Check parent node
		if (!(*tmp).getMark()) {
			(*tmp).setMark(true);
			break;
		}
		else {
			node = tmp;
		}
	}
	(*this).consolidate(fc);

}

/*=================================*
 * Method: FibHeap::delete_node
 * Created by FDChick
 *-----------------------------
 *   Remove the node with given id
 * if it exists in the heap
 *==================================*/
FibNode* FibHeap::delete_node(int id, bool fc(FibNode*, FibNode*))
{
	cout << "\t寻找该id的节点" << endl;
	// Find node with the id
	FibNode* node = (*(*this).min).idsearch(id);
	FibNode* ptr = (*(*this).min).getRight();
	while ((NULL == node) && (ptr != (*this).min)) {
		node = (*ptr).idsearch(id);
		ptr = (*ptr).getRight();
	}
	if (NULL == node) {
		cerr << "FibNode with given id not found" << endl;
		return NULL;
	}
	(*this).numitems--;

	cout << "\t消除子节点父节点信息" << endl;
	// set its child node as no parent node
	if (NULL != (*node).getChild()) {
		(*(*node).getChild()).setParent(NULL);

		FibNode* tmp = (*(*node).getChild()).getRight();
		while (tmp != (*node).getChild()) {
			(*tmp).setParent(NULL);
			tmp = (*tmp).getRight();
		}
		(*(*this).min).concat((*node).getChild());
	}
	(*node).setChild(NULL);
	(*node).setMark(false);

	cout << "\tB这里有没有输出？" << endl;
	// if the node is root node, remove it and return;
	if (NULL == (*node).getParent()) {
		(*(*node).getLeft()).setRight((*node).getRight());
		(*(*node).getRight()).setLeft((*node).getLeft());
		(*node).setLeft(NULL);
		(*node).setRight(NULL);
		(*this).consolidate(fc);
		return node;
	}
	// remove the node from its parent's children list
	if (node == (*node).getRight()) {
		(*(*node).getParent()).setChild(NULL);
	}
	else {
		(*(*node).getParent()).setChild((*node).getRight());
		// remove the node from sibling list
		(*(*node).getLeft()).setRight((*node).getRight());
		(*(*node).getRight()).setLeft((*node).getLeft());
	}

	(*node).setLeft(NULL);
	(*node).setRight(NULL);

	cout << "\t检查父节点" << endl;
	// test if its parent is marked
	FibNode* result = node;
	cout << node << endl;
	cout << node->getParent() << endl;
	cout << "\tLoop" << endl;
	if (NULL != (*node).getParent()) {
		node = (*node).getParent();
	}
	(*result).setParent(NULL);
	while (NULL != node) {
		// Set parent node marked if it is unmarked
		if (!(*node).getMark()) {
			cout << "\t父节点未标记！标记该父节点" << endl;
			(*node).setMark(true);
			break;
		}
		cout << "\t这里有问题吗？" << endl;
		// concat its children to root list
		if (NULL != (*node).getChild()) {
			(*(*this).min).concat((*node).getChild());
		}
		// remove the node from its parent's children list
		if (node == (*node).getRight()) {
			(*(*node).getParent()).setChild(NULL);
		}
		else {
			(*(*node).getParent()).setChild((*node).getRight());
			// remove the node from sibling list
			(*(*node).getLeft()).setRight((*node).getRight());
			(*(*node).getRight()).setLeft((*node).getLeft());
		}
		// insert the node to root list
		(*node).setMark(false);
		(*node).setLeft(NULL);
		(*node).setRight(NULL);
		(*node).setParent(NULL);
		(*(*this).min).append(node);

		node = (*node).getParent();
	}
	cout << "\t开始合并堆" << endl;
	(*this).consolidate(fc);
	cout << "删除完成" << endl;
	return result;
}