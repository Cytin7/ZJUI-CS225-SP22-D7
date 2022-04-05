//
// Created by FDChick on 2022/4/4.
//
#include <iostream>
#include "head.h"
#include <ctime>
using namespace std;
/*
 *
 * Created By FDChick on 2022/4/5
 * Here Are the functions to define
 * All the methods in the class
 * FibNode
 *
 */
//
// Construct Function
//
FibNode::FibNode(): LeftSib(this),
                    RightSib(this),
                    Parent(NULL),
                    Child(NULL),
                    mark_status(false),
                    degree(0){
    FibNode* LeftSib = this;
    FibNode* RightSib = this;
    // FibHeap node struct
    // Created by FDChick.
    // defining a circle sibling linked list.
    // Pointing to Parent and one of the Child node
    FibNode* Parent = NULL;
    FibNode* Child = NULL;
    // using when deleting node in the FibHeap.
    bool mark_status = false;
    // The degree of the node
    int degree = 0;
}
//
// Deconstruct function
//
FibNode::~FibNode() {
    cout << "one of the FibNode is leaving us... \n";
}
//
// void setLeftSib()
//
void FibNode::setLeftSib(FibNode* node) {
    this->LeftSib = node;
    node->RightSib = this;
}
//
// void setRightSib()
//
void FibNode::getRightSib(FibNode* node) {
    this->RightSib = node;
    node->LeftSib = this;
}
//
// void setParent()
//
void FibNode::setParent(FibNode *node) {
    this->Parent = node;
    node->Child = this;
}
//
// void setChild()
//
void FibNode::setChild(FibNode *node) {
    this->Child = node;
    node->Parent = this;
}
//
// Mark
// using when deleting node in the FibHeap.
//
bool FibNode::is_marked(){
    return mark_status;
}
void FibNode::mark(){
    if(is_marked()){
        cout << "Marking Error: The FibNode has been marked.\n"
    }else{
        mark_status = true;
    }
}
FibNode* FibNode::getLeftSib(){
    return LeftSib;
}
FibNode* FibNode::getRightSib(){
    return RightSib;
}
//
// Pointing to Parent and one of the Child node
//
FibNode* FibNode::getParent(){
    return Parent;
}
FibNode* FibNode::getChild(){
    return Child;
}
//
// ***********************************
// calc_priority_number() to calculate
// the priority number in the FibNode class
// Created By Peidong Yang.
// ***********************************
//
void FibNode::calc_priority_number()
//The most important criterion is the profession category followed by a ranking of age groups,
//and further followed by data and time of the registration.
//priority_number is an integer
//position:    6           5         4 3     2 1
//meaning:profession   age_group    month    day
{
    struct tm *info;
    info = gmtime(&(this->regist_time));
    int month = info->tm_mon;
    int day = info->tm_mday;
    this->priority_number = (this->profession) * 100000 + (this->age_group) * 10000 + month * 100 + day * 1;
}


/*
 *
 * Created By FDChick on 2022/4/5
 * Here Are the functions to define
 * All the methods in the class
 * FibHeap
 *
 */
FibHeap::FibHeap(){
    this->numitems = 0;
    this->maxDegree = 0;
    this->min = NULL;
    this->cons = NULL;
}
FibHeap::~FibHeap(){
    cout << "one of the FibHeap is leaving us forever.\n";
}
void FibHeap::Add_Node(FibNode* node, FibNode* root){
}
void Insert(FibNode* node);

// 移除斐波那契堆中的最小节点
void removeMin();
// 将other合并到当前堆中
void combine(FibHeap *other);
// 获取斐波那契堆中最小键值，并保存到pkey中；成功返回true，否则返回false。
bool minimum(int *pkey);
// 将斐波那契堆中键值oldkey更新为newkey
void update(int oldkey, int newkey);
// 删除键值为key的节点
void remove(int key);
// 斐波那契堆中是否包含键值key
bool contains(int key);
// 打印斐波那契堆
void print();
// 销毁
void destroy();
// Operations for Concat.
// to put one of the root linked list
// to the current root linked list.
// This is the same as to concat two double linked list.
void Concat_Node(FibNode* node1, FibNode* node2);
void Union_Heap(FibHeap* heap);

// Operation to pop out the min node.
// Directly to connect the min-node's sub-tree in to root list.
// concat all the trees that has the same degree until
// there is no trees have the same degree.
FibNode* Pop_Min();
/*
 * These Three are the operation to
 * consolidate the trees that have
 * the same degrees.
 */
void link_Node(FibNode* node, FibNode* root);
// renew the degree.
void renewDegree(FibNode *parent, int degree);
void Cons_Make();
void Consolidate();
// 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
void cut(FibNode *node, FibNode *parent);
// 对节点node进行"级联剪切"
void cascadingCut(FibNode *node) ;
// 将斐波那契堆中节点node的值减少为key
void decrease(FibNode *node, int key);
// 将斐波那契堆中节点node的值增加为key
void increase(FibNode *node, int key);
// 更新斐波那契堆的节点node的键值为key
void update(FibNode *node, int key);
// 在最小堆root中查找键值为key的节点
FibNode* search(FibNode *root, int key);
// 在斐波那契堆中查找键值为key的节点
FibNode* search(int key);
// 在最小堆root中查找键值为key的节点
FibNode* idsearch(FibNode *root, int id);
// 删除结点node
void remove(FibNode *node);
// 销毁斐波那契堆
void destroyNode(FibNode *node);
// 打印斐波那契堆
void print(FibNode*node, FibNode*prev, int direction)
