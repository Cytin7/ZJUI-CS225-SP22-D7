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
	}
	else {
		(*(*this).min).append(node);
		if (fc(node, (*this).min)) {
			(*this).min = node;
		}
	}
	(*this).numitems += 1;
	(*this).consolidate(fc);
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
	(*this).numitems -= 1;
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
	if (NULL == (*this).min || 0 == (*this).numitems) {
		return;
	}
	// re- calculate degree for all nodes
	FibNode* nodeptr = (*(*this).min).getRight();
	while (nodeptr != (*this).min) {
		(*nodeptr).updateDegree();
	}
	// create array arr for consolidate
	int Deg = (int)log2((*this).numitems) + 2;
	FibNode** arr = (FibNode**)calloc(Deg, sizeof(FibNode*));
	for (int i = 0; i < Deg; i++) {
		arr[i] = NULL;
	}

	FibNode* a, * b;
	int d;
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
	// re- calculate degree for all nodes
	FibNode* node = (*(*this).min).getRight();
	int max = (*(*this).min).updateDegree();
	int tmp;
	while (node != (*this).min) {
		tmp = (*node).updateDegree();
		if (max < tmp) {
			max = tmp;
		}
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
	FibNode* node = (*(*this).min).getRight();
	while (node != (*this).min) {
		node->setParent(NULL);
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
	FibNode* node = (*(*this).min).idsearch(id);
	if (NULL == node) {
		return;
	}
	{
		(*(*node).getChild()).setParent(NULL);
		FibNode* tmp = (*(*node).getChild()).getRight();
		while (tmp != (*node).getChild()) {
			(*tmp).setParent(NULL);
			tmp = (*tmp).getRight();
		}
		(*(*this).min).concat((*node).getChild());
		(*node).setChild(NULL);
	}
	FibNode* result = node;
	(*node).setMark(false);
	if (node == (*node).getRight()) {
		(*(*node).getParent()).setChild(NULL);
	}
	else {
		(*(*node).getParent()).setChild((*node).getRight());
		// remove the node from sibling list
		(*(*node).getLeft()).setRight((*node).getRight());
		(*(*node).getRight()).setLeft((*node).getLeft());
	}

	(*node).setParent(NULL);
	(*node).setLeft(NULL);
	(*node).setRight(NULL);
	(*node).setMark(false);
	node = (*node).getParent();
	// Check parent node
	if (!(*node).getMark()) {
		(*node).setMark(true);
		(*this).consolidate(fc);
		return result;
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
