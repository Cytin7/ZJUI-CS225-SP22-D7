//
// Created by FDChick on 2022/4/4.
//
#include <iostream>
#include "head.h"
#include <ctime>
#include <math.h>
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

void FibNode::mark(){
    if(mark_status){
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
int FibNode::getdegree() {
    return this->degree;
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
int FibNode::get_priority_number() {
    return priority_number;
}
void FibNode::priority_change(){
    this->priority_number = -1;
    return;
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
// 移除某个节点出双链表
void FibHeap::removeNode(FibNode *node){
    // node->left->right = node->right;
    // node->right->left = node->left;
    node->getRightSib()->setLeftSib(node->getLeftSib());
    node->getLeftSib()->setRightSib(node->getRightSib());
}
//
// This function called
// Add_Node used
// for add nodes to siblings
//
void FibHeap::Add_Node(FibNode* node, FibNode* root){
    FibNode* ptr = root->getRightSib();
    ptr->setLeftSib(node);
    node->setLeftSib(root);
}
//
// This function called
// Insert used
// for add nodes to siblings
//
void FibHeap::Insert(FibNode* node){
    if (numitems == 0){
        min = node;
    }else{
        Add_Node(node, min);
        if (node->get_priority_number() < min->get_priority_number()){
            min = node;
        }
    }
    numitems++;
}

// 移除斐波那契堆中的最小节点
void FibHeap::removeMin(){
    if ( min == NULL ){
        return;
    }
    FibNode* child = NULL;
    FibNode* m = min;
    // 将min每一个儿子(儿子和儿子的兄弟)都添加到"斐波那契堆的根链表"中
    while (m->getChild() != NULL){
        m->setChild(child);
        removeNode(child);
        if (child->getRightSib() == child) {
            m->setChild(NULL);
        }else{
            m->setChild(child->right);
        }
        Add_Node(child, min);
        child->setParent(NULL);
    }

    // 将m从根链表中移除
    removeNode(m);
    // 若m是堆中唯一节点，则设置堆的最小节点为NULL；
    // 否则，设置堆的最小节点为一个非空节点(m->right)，然后再进行调节。
    if (m->getRightSib() == m) {
        min = NULL;
    }else{
        min = m->getRightSib();
        Consolidate();
    }
    numitems--;
    delete m;
}
// 将other合并到当前堆中
void FibHeap::combine(FibHeap *other){
    if (other == NULL){
        return;
    }
    if (other->maxDegree > this->maxDegree){
        swap(*this, *other);
    }
    // this无"最小节点"
    if((this->min) == NULL){
        this->min = other->min;
        this->numitems = other->numitems;
        free(other->cons);
        delete other;
        // this有"最小节点" && other无"最小节点"
    }else if((other->min) == NULL){
        free(other->cons);
        delete other;
        // this有"最小节点" && other有"最小节点"
    }else{
        // 将"other中根链表"添加到"this"中
        catList(this->min, other->min);
        if (this->min->key > other->min->key){
            this->min = other->min;
        }
        this->numitems += other->numitems;
        free(other->cons);
        delete other;
    }
}
// 将斐波那契堆中的node更新为newkey
void FibHeap::update(FibNode* node, int temp){
    if ( min == NULL || node ==  NULL ){
        return;
    }
    int key = node->get_priority_number();
    if ( key < temp ){
        decrease(node, key);
    }else if ( key > temp ){
        increase(node, key);
    }else{
        cout << "Update Error: No need to update." << endl;
    }
}
// 删除键值为key的节点
void FibHeap::remove(FibNode* node){
    int m = min->get_priority_number()-1;
    decrease(node, m-1);
    removeMin();
    node->calc_priority_number();
    return;
}
// 打印斐波那契堆
void FibHeap::print(){
    int i = 0;
    FibNode *p;
    if ( min == NULL ){
        return;
    }
    cout << "== 斐波那契堆的详细信息: ==" << endl;
    p = min;
    do {
        i++;
        cout << setw(2) << i << ". " << setw(4) << p->get_priority_number() << "(" << p->getdegree() << ") is root" << endl;
        print(p->getChild(), p, 1);
        p = p->getRightSib();
    } while (p != min);
    cout << endl;
}
// 销毁
void FibHeap::destroy(){
    destroyNode(min);
    free(cons);
}

// Operation to pop out the min node.
// Directly to connect the min-node's sub-tree in to root list.
// concat all the trees that has the same degree until
// there is no trees have the same degree.
FibNode* FibHeap::Pop_Min(){
    FibNode* p = min;
    if (p == p->getRightSib()){
        min = NULL;
    }else{
        removeNode (p);
        min = p->getRightSib();
    }
    p->setLeftSib(p);
    p->setRightSib(p);
    return p;
}
/*
 * These Three are the operation to
 * consolidate the trees that have
 * the same degrees.
 */
void FibHeap::link_Node(FibNode* node, FibNode* root){
    // 将node从双链表中移除
    removeNode(node);
    // 将node设为root的孩子
    if (root->getChild() == NULL){
        root->setChild(node);
    }else{
        Add_Node(node, root->getChild());
    }
    node->setParent(root);
    root->degree++;
    node->mark_status = false;
    return;
}
// renew the degree.
void FibHeap::renewDegree(FibNode *parent, int degree){
    parent->degree -= degree;
    if (parent->getParent() != NULL){
        renewDegree(parent->parent, degree);
    }
    return;
}
void FibHeap::Cons_Make(){
    int prev = maxDegree;
    maxDegree = (log(numitems)/log(2.0)) + 1;
    if (prev >= maxDegree){
        return;
    }
    cons = (FibNode**) realloc(cons, sizeof(FibHeap *) * (maxDegree + 1));
    return;
}
void FibHeap::Consolidate(){
    int i, d, D;
    FibNode *x, *y, *tmp;
    Cons_Make();
    D = maxDegree + 1;
    for (i = 0; i < D; i++){
        cons[i] = NULL;
    }
    while (min != NULL){
        x = Pop_Min();                // 取出堆中的最小树(最小节点所在的树)
        d = x->degree;                    // 获取最小树的度数
        // cons[d] != NULL，意味着有两棵树(x和y)的"度数"相同。
        while (cons[d] != NULL){
            y = cons[d];                // y是"与x的度数相同的树"
            if (x->get_priority_number() > y->get_priority_number()){
                swap(x, y);
            }
            link_Node(y, x);    // 将y链接到x中
            cons[d] = NULL;
            d++;
        }
        cons[d] = x;
    }
    min = NULL;
    // 将cons中的结点重新加到根表中
    for (i=0; i<D; i++){
        if (cons[i] != NULL){
            if (min == NULL){
                min = cons[i];
            }else{
                Add_Node(cons[i], min);
                if ((cons[i])->get_priority_number()< min->get_priority_number()){
                    min = cons[i];
                }
            }
        }
    }
    return;
}
// 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
void FibHeap::cut(FibNode *node, FibNode *parent){
    removeNode(node);
    renewDegree(parent, node->degree);
    // node没有兄弟
    if (node == node->getRightSib()){
        parent->setChild(NULL);
    }else{
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
void FibHeap::cascadingCut(FibNode *node){
    FibNode* parent = node->getParent();
    if (parent != NULL) {
        if (node->mark_status == false){
            node->mark_status = true;
        }else{
            cut(node, parent);
            cascadingCut(parent);
        }
    }
    return;
}
// 将斐波那契堆中节点node的值减少为key
void FibHeap::decrease(FibNode *node, int key){
    FibNode *parent = node->parent;
    if (parent!=NULL && key < parent->get_priority_number()){
        // 将node从父节点parent中剥离出来，并将node添加到根链表中
        cut(node, parent);
        cascadingCut(parent);
    }
    if (key < min->get_priority_number()){
        min = node;
    }
    return;
}
// 将斐波那契堆中节点node的值增加为key
void FibHeap::increase(FibNode *node, int key){
    FibNode *child, *parent, *right;
    // 将node每一个儿子(不包括孙子,重孙,...)都添加到"斐波那契堆的根链表"中
    while (node->getChild() != NULL){
        child = node->getChild();
        removeNode(child);
        if ( child->getRightSib() == child ){
            node->setChild(NULL);
        }else{
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
    parent = node->parent;
    if(parent != NULL){
        cut(node, parent);
        cascadingCut(parent);
    }else if ( min == node ){
        right = node->getRightSib();
        while(right != node){
            if(key > right->get_priority_number()){
                min = right;
            }
            right = right->getRightSib();
        }
    }
    return;
}
// 在最小堆root中查找键值为key的节点
FibNode* FibHeap::idsearch(FibNode* root ,int id){
    FibNode *t = root;    // 临时节点
    FibNode *p = NULL;    // 要查找的节点
    if ( root == NULL ){
        return root;
    }
    do{
        if (t->getRecordID() == id){
            p = t;
            break;
        }else{
            if ((p = search(t->getChild(), id)) != NULL){
                break;
            }
        }
        t = t->getRightSib();
    } while (t != root);
    return p;
}
// 删除结点node
void FibHeap::remove(FibNode *node){
    int temp = node->get_priority_number();
    node->priority_change();
    update(node,temp);
    removeMin();
    node->calc_priority_number();
    return;
}
// 销毁斐波那契堆
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
}
// 打印斐波那契堆
void FibHeap::print(FibNode*node, FibNode*prev, int direction){
    FibNode* start = node;
    if (node==NULL)
        return ;
    do{
        if (direction == 1){
            cout << setw(8) << node->get_priority_number() << "the degree is (" << node->getdegree() << ") is "<< setw(2) << prev->get_priority_number() << "'s child" << endl;
        }else{
            cout << setw(8) << node->get_priority_number() << "the degree is (" << node->getdegree() << ") is "<< setw(2) << prev->get_priority_number() << "'s next" << endl;
        }
        if (node->child != NULL){
            print(node->child, node, 1);
        }
        // 兄弟节点
        prev = node;
        node = node->getRightSib();
        direction = 2;
    } while(node != start);
}
