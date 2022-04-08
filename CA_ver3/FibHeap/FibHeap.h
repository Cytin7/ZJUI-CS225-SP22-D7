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
	// �Ƴ�ĳ���ڵ��˫����
	void removeNode(FibNode* node);
	// Operations for insertion.
	// To insert the new node just before the root linked list.
	// Then compare min and this node,
	// if the node is smaller,
	// then refresh the min to be the insert node.
	/* The Fib_Node_Add is used to complete the linked list operation.
	 * And the Insert is truly insertion. */
	void Add_Node(FibNode* node, FibNode* root);
	// ͨ���ڵ�ָ�����ڵ�
	void Insert(FibNode* node);
	// �Ƴ�쳲��������е���С�ڵ�
	void removeMin();
	// ��other�ϲ�����ǰ����
	/*
	 * // ��other�ϲ�����ǰ����
	 * void combine(FibHeap* other);
	 */
	 // ��쳲��������е�node����Ϊnewkey
	void update(FibNode* node, int temp);
	// ɾ�����node
	void remove(FibNode* node);
	// ��ӡ쳲�������!
	void print();
	// ����
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
	// ��node�Ӹ��ڵ�parent���������а����������ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
	void cut(FibNode* node, FibNode* parent);
	// �Խڵ�node����"��������"
	void cascadingCut(FibNode* node);
	// ��쳲��������нڵ�node��ֵ����Ϊkey
	void decrease(FibNode* node, int key);
	// ��쳲��������нڵ�node��ֵ����Ϊkey
	void increase(FibNode* node, int key);
	// �������Ҽ�ֵΪkey�Ľڵ�
	FibNode* idsearch(FibNode* root, int id);
	FibNode* getMin();
private:
	// ����쳲�������
	//void destroyNode(FibNode* node);
	// ��ӡ쳲�������
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