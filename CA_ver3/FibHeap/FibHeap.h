#pragma once
// Multiple head file only include once

// Include our head files
#include "../FibNode/FibNode.h"

/*========================================*
 * Class: FibHeap
 * 
 * Created by FDChick
 *--------------------
 * Introduction:
 *     Fibonacci heap structure
 *========================================*/
class FibHeap 
{
public:
	// construct & deconstruct
	FibHeap();
	~FibHeap();
	// 移除某个节点出双链表
	void removeNode(FibNode* node);
	// Operations for insertion.
	// To insert the new node just before the root linked list.
	// Then compare min and this node,
	// if the node is smaller,
	// then refresh the min to be the insert node.
	/* The Fib_Node_Add is used to complete the linked list operation.
	 * And the Insert is truly insertion. */
	void Add_Node(FibNode* node, FibNode* root);
	// 通过节点指针插入节点
	void Insert(FibNode* node);
	// 移除斐波那契堆中的最小节点
	void removeMin();
	// 将other合并到当前堆中
	/*
	 * // 将other合并到当前堆中
	 * void combine(FibHeap* other);
	 */
	 // 将斐波那契堆中的node更新为newkey
	void update(FibNode* node, int temp);
	// 删除结点node
	void remove(FibNode* node);
	// 打印斐波那契堆!
	void print();
	// 销毁
	//void destroy();

	// Operation to pop out the min node.
	// Directly to connect the min-node's sub-tree in to root list.
	// concat all the trees that has the same degree until
	// there is no trees have the same degree.
	FibNode* Pop_Min();
	FibNode* extractMin();
	/*
	 * These Three are the operation to
	 * consolidate the trees that have
	 * the same degrees.
	 */
	void link_Node(FibNode* node, FibNode* root);
	// renew the degree.
	void renewDegree(FibNode* parent, int degree);
	void Cons_Make();
	void Consolidate();
	// 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
	void cut(FibNode* node, FibNode* parent);
	// 对节点node进行"级联剪切"
	void cascadingCut(FibNode* node);
	// 将斐波那契堆中节点node的值减少为key
	void decrease(FibNode* node, int key);
	// 将斐波那契堆中节点node的值增加为key
	void increase(FibNode* node, int key);
	// 遍历查找键值为key的节点
	FibNode* idsearch(FibNode* root, int id);
	FibNode* getMin();
private:
	// 销毁斐波那契堆
	//void destroyNode(FibNode* node);
	// 打印斐波那契堆
	void print(FibNode* node, FibNode* prev, int direction);
	// some characters.
	int numitems;
	int maxDegree;
	FibNode* min;
	FibNode** cons;

	// Peidong
public:
	bool withdraw(FibNode* withdraw_node, FibHeap* main_heap1, FibHeap* main_heap2, FibHeap* withdraw_heap);
	bool modify(FibNode* modified_node, int information_type, int new_information, FibHeap* main_heap1, FibHeap* main_heap2, FibHeap* medium_risk_heap, FibHeap* high_risk_heap, FibHeap* withdraw_heap);
	FibNode* find_node(int id, FibHeap* main_heap, FibHeap* medium_risk_heap, FibHeap* high_risk_heap, FibHeap* withdraw_heap);
	void LoopMinus(FibNode* ptr);

};