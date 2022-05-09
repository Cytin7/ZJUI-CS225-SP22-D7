#include "FibHeap.h"

// construct functon of class ListNode
FibHeap::FibHeap()
{
	(*this).numitems = 0;
	//(*this).maxDegree = 0;
	(*this).min = nullptr;
}

FibHeap::~FibHeap()
{
}

// return variables
int FibHeap::getNumitems()
{
	return (*this).numitems;
}
//int FibHeap::getMaxDegree()
//{
//	return (*this).maxDegree;
//}
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
		(*this).numitems += 1;
		(*this).min = node;
	}
	else {
		(*(*this).min).append(node);
		//cout << "\t\t添加节点" << endl;
		if (fc(node, (*this).min)) {
			(*this).min = node;
		}
		//cout << "\t\t目前节点数：" << (*this).numitems << endl;
		(*this).numitems += 1;
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
 //void FibHeap::combine(FibHeap* heap, bool fc(FibNode*, FibNode*))
 //{
 //	if (nullptr == heap || 0 == (*heap).numitems) {
 //		return;
 //	}
 //	if (0 == (*this).numitems) {
 //		(*this).numitems = (*heap).numitems;
 //		(*this).maxDegree = (*heap).maxDegree;
 //		(*this).min = (*heap).min;
 //		delete heap;
 //		return;
 //	}
 //	(*(*this).min).concat((*heap).min);
 //	if (fc((*heap).min, (*this).min)) {
 //		(*this).min = (*heap).min;
 //	}
 //	(*this).numitems += (*heap).numitems;
 //	delete heap;
 //	(*this).consolidate(fc);
 //	return;
 //}

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
	if (nullptr == (*this).min) {
		cout << "Error: the heap is already empty." << endl;
		return nullptr;
	}
	FibNode* min_node = (*this).min;
	if (min_node == (*min_node).getRight()) {
		(*this).min = nullptr;
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
	if (nullptr == (*this).min || 0 == (*this).numitems) {
		return;
	}
	cout << "\t\t发生什么事了B" << endl;
	// re- calculate degree for all nodes
	FibNode* nodeptr = (*(*this).min).getRight();
	while (nodeptr != (*this).min) {
		(*nodeptr).updateDegree();
		nodeptr = (*nodeptr).getRight();
	}
	cout << "\t\t发生什么事了D" << endl;
	// create array arr for consolidate
	int Deg = (int)log2((*this).numitems) + 2;
	FibNode** arr = (FibNode**)calloc(Deg, sizeof(FibNode*));
	for (int i = 0; i < Deg; i++) {
		arr[i] = nullptr;
	}
	FibNode* a, * b;
	int d;
	cout << "\t\t发生什么事了E" << endl;
	// remove min_tree and murge
	while (nullptr != (*this).min) {
		a = this->remove_min_tree(fc);
		d = (*a).getDegree();
		while (!(arr[d] == nullptr)) {
			b = arr[d];
			if (fc(a, b)) {
				(*a).addChild(b);
			}
			else {
				(*b).addChild(a);
				a = b;
			}
			arr[d] = nullptr;
			d++;
		}
		arr[d] = a;
	}
	// concat back the nodes.
	cout << "\t\t发生什么事了F" << endl;
	for (int i = 0; i < Deg; i++) {
		if (arr[i] != nullptr) {
			if (nullptr == (*this).min) {
				(*this).min = arr[i];
			}
			else {
				(*(*this).min).append(arr[i]);
				/*if (fc(arr[i], (*this).min)) {
					(*this).min = arr[i];
				}*/
			}
		}
	}
	(*this).reset_min(fc);
	cout << "\t\t发生什么事了G" << endl;
	//// re- calculate degree for all nodes
	//FibNode* node = (*(*this).min).getRight();
	//int max = (*(*this).min).updateDegree();
	//int tmp;
	////system("pause");
	//while (node != (*this).min) {
	//	tmp = (*node).updateDegree();
	//	cout << "\t\t============" << endl;
	//	if (max < tmp) {
	//		max = tmp;
	//	}
	//	node = (*node).getRight();
	//}
	//(*this).maxDegree = max;
	free(arr);
	return;
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
	if (nullptr == this || 0 == (*this).numitems) {
		return nullptr;
	}
	FibNode* min_node = (*this).min;
	(*min_node).setParent(nullptr);
	// set all min's children's parent to nullptr
	if (nullptr != (*min_node).getChild()) {
		(*(*min_node).getChild()).setParent(nullptr);
		FibNode* node = (*(*min_node).getChild()).getRight();
		while (node != (*min_node).getChild()) {
			(*node).setParent(nullptr);
			node = (*node).getRight();
		}
		(*min_node).concat(node);
	}

	// remove the min node
	if (min_node == (*min_node).getRight()) {
		(*this).min = nullptr;
	}
	else {
		(*this).min = (*min_node).getRight();
		(*(*min_node).getLeft()).setRight((*min_node).getRight());
		(*(*min_node).getRight()).setLeft((*min_node).getLeft());
		(*this).reset_min(fc);
		(*this).consolidate(fc);
	}
	(*this).numitems -= 1;
	(*min_node).setChild(nullptr);
	(*min_node).setLeft(nullptr);
	(*min_node).setRight(nullptr);
	return min_node;
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
	if ((nullptr == this) || (nullptr == (*this).min)) {
		// if the heap is empty
		return;
	}
	FibNode* node = (*(*this).min).idsearch(id);
	if (nullptr == node) {
		// if the node with the given id was not found
		return;
	}
	// Check the influence of the update
	if (((nullptr == (*node).getParent()) || (fc((*node).getParent(), node))) && (nullptr != (*node).getChild())) {
		// If priority down
		(*(*node).getChild()).setParent(nullptr);
		FibNode* tmp = (*(*node).getChild()).getRight();
		while (tmp != (*node).getChild()) {
			(*tmp).setParent(nullptr);
			tmp = (*tmp).getRight();
		}
		(*(*this).min).concat((*node).getChild());
		(*node).setChild(nullptr);
	}

	FibNode* father = (*node).getParent();
	while (nullptr != father) {
		(*node).setMark(false);
		if (node == (*node).getRight()) {
			(*father).setChild(nullptr);
		}
		else {
			(*father).setChild((*node).getRight());
			// remove the node from sibling list
			(*(*node).getLeft()).setRight((*node).getRight());
			(*(*node).getRight()).setLeft((*node).getLeft());
		}

		(*node).setParent(nullptr);
		(*node).setLeft(nullptr);
		(*node).setRight(nullptr);
		// append the node to the roots
		(*(*this).min).append(node);

		// Check parent node
		if (!(*father).getMark()) {
			(*father).setMark(true);
			break;
		}
		else {
			node = father;
			father = (*node).getParent();
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
	if (nullptr == (*this).min) {
		return nullptr;
	}
	// Find node with the id
	FibNode* node = (*(*this).min).idsearch(id);
	FibNode* ptr = (*(*this).min).getRight();
	while ((nullptr == node) && (ptr != (*this).min)) {
		node = (*ptr).idsearch(id);
		ptr = (*ptr).getRight();
	}
	if (nullptr == node) {
		return nullptr;
	}
	(*this).numitems--;

	// set its child node as no parent node
	if (nullptr != (*node).getChild()) {
		(*(*node).getChild()).setParent(nullptr);

		FibNode* tmp = (*(*node).getChild()).getRight();
		while (tmp != (*node).getChild()) {
			(*tmp).setParent(nullptr);
			tmp = (*tmp).getRight();
		}
		(*(*this).min).concat((*node).getChild());
	}
	(*node).setChild(nullptr);
	(*node).setMark(false);

	// if the node is root node, remove it and return;
	if (nullptr == (*node).getParent()) {
		(*(*node).getLeft()).setRight((*node).getRight());
		(*(*node).getRight()).setLeft((*node).getLeft());
		(*node).setLeft(nullptr);
		(*node).setRight(nullptr);
		(*this).consolidate(fc);
		return node;
	}
	// remove the node from its parent's children list
	if (node == (*node).getRight()) {
		(*(*node).getParent()).setChild(nullptr);
	}
	else {
		(*(*node).getParent()).setChild((*node).getRight());
		// remove the node from sibling list
		(*(*node).getLeft()).setRight((*node).getRight());
		(*(*node).getRight()).setLeft((*node).getLeft());
	}

	(*node).setLeft(nullptr);
	(*node).setRight(nullptr);

	// test if its parent is marked
	FibNode* result = node;
	cout << node << endl;
	cout << node->getParent() << endl;
	if (nullptr != (*node).getParent()) {
		node = (*node).getParent();
	}
	FibNode* father;
	while (nullptr != node) {
		(*node).setParent(nullptr);
		// Set parent node marked if it is unmarked
		if (!(*node).getMark()) {
			(*node).setMark(true);
			break;
		}
		// concat its children to root list
		if (nullptr != (*node).getChild()) {
			(*(*this).min).concat((*node).getChild());
		}
		// Test its parent
		if (nullptr != (*node).getParent()) {

			father = (*node).getParent();
			// remove the node from its parent's children list
			if (node == (*node).getRight()) {
				(*father).setChild(nullptr);
			}
			else {
				(*father).setChild((*node).getRight());
				// remove the node from sibling list
				(*(*node).getLeft()).setRight((*node).getRight());
				(*(*node).getRight()).setLeft((*node).getLeft());
			}

			// insert the node to root list
			(*node).setMark(false);
			(*node).setLeft(nullptr);
			(*node).setRight(nullptr);
			(*node).setParent(nullptr);
			(*(*this).min).append(node);

			node = father;
		}
		else {
			node = nullptr;
		}
	}
	(*this).consolidate(fc);
	(*result).setParent(nullptr);
	return result;
}