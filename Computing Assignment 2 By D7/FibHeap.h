#pragma once
// Multiple head file only include once

// Include libraries
#include <cmath>
#include <iomanip>
// Include our head files
#include "FibNode.h"
#include "Record.h"

class FibHeap {
private:
    int keyNum;
    int maxDegree;
    FibNode *min;
    FibNode **cons;
    int type;

public:
    FibHeap(int type);
    ~FibHeap();
    // new need: return the type of the heap.
    int getType();
    // Modified, insert a existing record into a certain heap.
    void insert(Record* record);
    void removeMin();
    void combine(FibHeap *other);
    bool minimum(int *pkey);
    // Modified, do while we update the records,
    // we should update the key value of nodes in the FIbHeap;
    void update(int oldkey, int newkey);
    void update(Record* record);
    // Modified, delete the FibNode with certain record pointer.
    // void remove(int key);
    void remove(Record* record);
    void remove(int id);
    // Modified, to search in to heap
    // to find a node with certain id/Record;
    // bool contains(int key);
    // the exactly same function as idSearch.
    bool contains(int key);
    FibNode* search(int key);
    FibNode* idSearch(int id);
    FibNode* recordSearch(Record* record);
    void print();
    void destroy();
public:
    FibNode* getMin();
    int getNumitems();
    // FibHeap operations
    void insert(FibNode* node, bool fc(FibNode*, FibNode*));
    // void combine(FibHeap* heap, bool fc(FibNode*, FibNode*));
    void reset_min(bool fc(FibNode*, FibNode*));
    FibNode* remove_min_tree(bool fc(FibNode*, FibNode*));
    void consolidate(bool fc(FibNode*, FibNode*));
    FibNode* pop_min(bool fc(FibNode*, FibNode*));
    void update(int id, bool fc(FibNode*, FibNode*));
    FibNode* delete_node(int id, bool fc(FibNode*, FibNode*));
    void insert(FibNode *node);
    void remove(FibNode* node);

private:
    void removeNode(FibNode *node);
    void addNode(FibNode *node, FibNode *root);
    void catList(FibNode *a, FibNode *b);
    FibNode* extractMin();
    void link(FibNode* node, FibNode* root);
    void makeCons();
    void consolidate();
    void renewDegree(FibNode *parent, int degree);
    void cut(FibNode *node, FibNode *parent);
    void cascadingCut(FibNode *node);
    void decrease(FibNode *node, int key);
    void increase(FibNode *node, int key);
    void update(FibNode *node, int key);
    FibNode* search(FibNode *root, int key);
    // as search cannot be modified
    // in this class, so we add
    // a recursive idSearch function.
    FibNode* idSearch(FibNode* root, int id);
    FibNode* recordSearch(FibNode* root, Record* record);
    void destroyNode(FibNode *node);
    void print(FibNode *node, FibNode *prev, int direction);
};

FibNode* FibHeap::getMin() {
    return min;
}

int FibHeap::getNumitems() {
    return keyNum;
}

void FibHeap::insert(FibNode *node, bool (*fc)(FibNode *, FibNode *)) {
    (*this).insert(node);
}

void FibHeap::reset_min(bool (*fc)(FibNode *, FibNode *)) {
    FibNode* temp = min;
    FibNode* minimum = min;
    while (temp->right != min){
        if (minimum->key > temp->right->key){
            minimum = temp->right;
            temp = temp->right;
        }else{
            temp = temp->right;
        }
    }
    min = minimum;
    return;
}

FibNode *FibHeap::remove_min_tree(bool (*fc)(FibNode *, FibNode *)) {
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

FibNode *FibHeap::pop_min(bool (*fc)(FibNode *, FibNode *)) {
    if (0 == (*this).keyNum) {
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
    (*this).keyNum -= 1;
    (*min_node).setChild(nullptr);
    (*min_node).setLeft(nullptr);
    (*min_node).setRight(nullptr);
    return min_node;
}

void FibHeap::update(int id, bool (*fc)(FibNode *, FibNode *)) {
    FibNode* ptr = idSearch(id);
    update(ptr->record);
    return;
}

FibNode *FibHeap::delete_node(int id, bool (*fc)(FibNode *, FibNode *)) {
    FibNode* ptr = idSearch(id);
    remove(id);
    return ptr;
}

FibHeap::FibHeap(int type)
{
    keyNum = 0;
    maxDegree = 0;
    min = NULL;
    cons = NULL;
    (*this).type = type;
    return;
}

FibHeap::~FibHeap()
{
}

/*
 * Get the type/ kind of the FibHeap
 * type == 1 as the mainheap.
 * type == 2 as the ddlheap.
 * type == 3 as the highrisk heap.
 */
int FibHeap::getType() {
    if (type == 1)
        cout << "This FibHeap is the MainHeap to arrange normal people." << endl;
    else if (type == 2)
        cout << "This FibHeap is the DeadlineHeap to arrange people who has deadline to have treatment.." << endl;
    else
        cout << "This FibHeap is the HighRiskHeap." << endl;
    return type;
}

/*
 * 将node从双链表移除
 */
void FibHeap::removeNode(FibNode *node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}

/*
 * Add node to the heap before node
 * a …… root
 * a …… node …… root
*/
void FibHeap::addNode(FibNode *node, FibNode *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

/*
 * Insert the node node into the Fibonacci heap
 */
void FibHeap::insert(FibNode *node)
{
    if ((*node).type != (*this).type){
        cout << "insertion Error: type not fit into the current type." << endl;
        return;
    }
    if (keyNum == 0)
        min = node;
    else
    {
        addNode(node, min);
        if (node->key < min->key)
            min = node;
    }
    keyNum++;
}

/*
 * Create a new node with key value and insert it into Fibonacci heap
 */
void FibHeap::insert(Record* record)
{
    FibNode *node;
    node = new FibNode(type,record);
    if (node == NULL)
        return;
    insert(node);
    return;
}

/*
 * Link the two-way linked list B to the back of the two-way linked list a
 *
 * Note: both a and B here are bidirectional linked lists
 */
void FibHeap::catList(FibNode *a, FibNode *b)
{
    FibNode *tmp;
    tmp            = a->right;
    a->right       = b->right;
    b->right->left = a;
    b->right       = tmp;
    tmp->left      = b;
}


/*
 * Merge other into the current heap
 */
void FibHeap::combine(FibHeap *other)
{
    if (other==NULL)
        return ;

    if(other->maxDegree > this->maxDegree)
        swap(*this, *other);

    if((this->min) == NULL)
    {
        this->min = other->min;
        this->keyNum = other->keyNum;
        free(other->cons);
        delete other;
    }
    else if((other->min) == NULL)
    {
        free(other->cons);
        delete other;
    }
    else
    {
        catList(this->min, other->min);

        if (this->min->key > other->min->key)
            this->min = other->min;
        this->keyNum += other->keyNum;
        free(other->cons);
        delete other;
    }
}

/*
 * Remove the "minimum node of heap" from the root linked list,
 * This means "remove the tree to which the smallest node belongs" from the heap!
 */
FibNode* FibHeap::extractMin()
{
    FibNode *p = min;

    if (p == p->right)
        min = NULL;
    else
    {
        removeNode(p);
        min = p->right;
    }
    p->left = p->right = p;

    return p;
}

/*
 * Link node to root node
 */
void FibHeap::link(FibNode* node, FibNode* root)
{
    // Remove node from the double linked list
    removeNode(node);
    // Children who set node as root
    if (root->child == NULL)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->mark = false;
}

/*
 * Space required to create consolidate
 */
void FibHeap::makeCons()
{
    int old = maxDegree;
    // Calculate log2 (keynum), "+ 1" means rounding up!
    // Ex. log2 (13) = 3, rounded up to 3 + 1 = 4.
    maxDegree = (log(keyNum)/log(2.0)) + 1;
    if (old >= maxDegree)
        return ;
    // Because the degree is maxdegree and may be merged, maxdegree + 1 is required
    cons = (FibNode **)realloc(cons,sizeof(FibHeap *) * (maxDegree + 1));
}

/*
 * Merge the trees of the same degree in the root linked list of Fibonacci pile
 */
void FibHeap::consolidate()
{
    int i, d, D;
    FibNode *x, *y, *tmp;
    makeCons();
    D = maxDegree + 1;
    for (i = 0; i < D; i++)
        cons[i] = NULL;
    // Merge the root nodes of the same degree to make the tree unique for each degree
    while (min != NULL)
    {
        min->updateDegree();
        x = extractMin();                 //Take out the smallest tree in the heap (the tree where the smallest node is located.
        d = x->degree;                    //Gets the degree of the smallest tree.
                                          // cons[d] !=  Null, which means that two trees (x and y) have the same "degree".
        while (cons[d] != NULL)
        {
            y = cons[d];                  //Y is "a tree with the same degree as X"
            if (x->key > y->key)          //Ensure that the key value of X is smaller than y
                swap(x, y);
            link(y, x);
            cons[d] = NULL;
            d++;
        }
        cons[d] = x;
    }
    min = NULL;

    for (i=0; i<D; i++)
    {
        if (cons[i] != NULL)
        {
            if (min == NULL)
                min = cons[i];
            else
            {
                addNode(cons[i], min);
                if ((cons[i])->key < min->key)
                    min = cons[i];
            }
        }
    }
}

void FibHeap::consolidate(bool (*fc)(FibNode *, FibNode *)) {
    consolidate();
    return;
}

/*
 * Remove the min node.
 */
void FibHeap::removeMin()
{
    if (min==NULL)
        return ;
    FibNode *child = NULL;
    FibNode *m = min;
    while (m->child != NULL)
    {
        child = m->child;
        removeNode(child);
        if (child->right == child)
            m->child = NULL;
        else
            m->child = child->right;
        addNode(child, min);
        child->parent = NULL;
    }
    removeNode(m);
    // If M is the only node in the heap, set the minimum node of the heap to null;
    // Otherwise, set the minimum node of the heap as a non empty node (M - > right), and then adjust it.
    if (m->right == m)
        min = NULL;
    else
    {
        min = m->right;
        consolidate();
    }
    keyNum--;
    delete m;
}

/*
 * Obtain the minimum key value in Fibonacci heap and save it to pkey; If successful, return true; otherwise, return false.
 */
bool FibHeap::minimum(int *pkey)
{
    if (min==NULL || pkey==NULL)
        return false;

    *pkey = min->key;
    return true;
}

/*
 * renew degree of the current FibNode.
 */
void FibHeap::renewDegree(FibNode *parent, int degree)
{
    parent->degree -= degree;
    if (parent-> parent != NULL)
        renewDegree(parent->parent, degree);
}

/*
 * Split the node from the child link of the parent node,
 * And make node a member of the "root linked list of the heap".
 */
void FibHeap::cut(FibNode *node, FibNode *parent)
{
    removeNode(node);
    renewDegree(parent, node->degree);
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->mark = false;
    addNode(node, min);
}

/*
 * Cascade cut node
 *
 * Cascade shear: if the reduced node destroys the minimum heap property,
 * Then cut it off (that is, delete it from the two-way linked list, and
 * It is inserted into the two-way linked list formed by the minimum tree root node),
 * Then recursively perform cascade pruning from the "parent node of the cut node" to the root node of the tree
 */
void FibHeap::cascadingCut(FibNode *node)
{
    FibNode *parent = node->parent;
    if (parent != NULL)
    {
        if (node->mark == false)
            node->mark = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

/*
 * Reduce the value of node in Fibonacci heap to key
 */
void FibHeap::decrease(FibNode *node, int key)
{
    FibNode *parent;
    if (min==NULL ||node==NULL)
        return ;
    if ( key>=node->key)
    {
        cout << "decrease failed: the new key(" << key <<") "
             << "is no smaller than current key(" << node->key <<")" << endl;
        return ;
    }
    node->key = key;
    parent = node->parent;
    if (parent!=NULL && node->key < parent->key)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    if (node->key < min->key)
        min = node;
}

/*
 * Increase the value of node in Fibonacci heap to key
 */
void FibHeap::increase(FibNode *node, int key)
{
    FibNode *child, *parent, *right;

    if (min==NULL ||node==NULL)
        return ;

    if (key <= node->key)
    {
        cout << "increase failed: the new key(" << key <<") "
             << "is no greater than current key(" << node->key <<")" << endl;
        return ;
    }
    while (node->child != NULL)
    {
        child = node->child;
        removeNode(child);
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;
        addNode(child, min);
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // If node is not in the root list,
    // The node is removed from the child of the parent node
    // And make node a part of the "root linked list of the heap"
    // Then "cascade cutting" is performed
    // Otherwise, judge whether to update the minimum node of the heap
    parent = node->parent;
    if(parent != NULL)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    else if(min == node)
    {
        right = node->right;
        while(right != node)
        {
            if(node->key > right->key)
                min = right;
            right = right->right;
        }
    }
}

/*
 * 更新斐波那契堆的节点node的键值为key
 */
void FibHeap::update(FibNode *node, int key)
{
    if(key < node->key)
        decrease(node, key);
    else if(key > node->key)
        increase(node, key);
    else
        cout << "No need to update!!!" << endl;
}


void FibHeap::update(int oldkey, int newkey)
{
    FibNode *node;

    node = search(oldkey);
    if (node!=NULL)
        update(node, newkey);
}

void FibHeap::update(Record *record) {
    if (recordSearch(record) != nullptr)
        recordSearch(record)->calcKey();
    else
        cout << "recordUpdateError: record not found in this heap" << endl;
}

/*
 * Find the node with key value in the minimum heap root
 */
FibNode* FibHeap::search(FibNode *root, int key)
{
    FibNode *t = root;
    FibNode *p = NULL;
    if (root==NULL)
        return root;
    do{
        if (t->key == key){
            p = t;
            break;
        }else{
            if ((p = search(t->child, key)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);
    return p;
}

FibNode *FibHeap::idSearch(FibNode *root, int id) {
    FibNode *t = root;
    FibNode *p = NULL;
    if (root==NULL)
        return root;
    do{
        if (t->record->getRecordID() == id){
            p = t;
            break;
        }else{
            if ((p = idSearch(t->child, id)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);
    return p;
}

FibNode *FibHeap::recordSearch(FibNode *root, Record *record) {
    FibNode *t = root;
    FibNode *p = NULL;
    if (root==NULL)
        return root;
    do{
        if (t->record == record){
            p = t;
            break;
        }else{
            if ((p = recordSearch(t->child, record)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);
    return p;
}

/*
 * Find the node with key value in Fibonacci heap
 */
FibNode* FibHeap::search(int key)
{
    if (min==NULL)
        return NULL;
    return search(min, key);
}

FibNode *FibHeap::idSearch(int id) {
    if (min == nullptr)
        return nullptr;
    return idSearch(min,id);
}

FibNode *FibHeap::recordSearch(Record *record) {
    if (min == nullptr)
        return nullptr;
    return recordSearch(min,record);
}

/*
 * Whether there is a node with key value in Fibonacci heap.
 * Returns true if it exists, otherwise false.
 */
bool FibHeap::contains(int key)
{
    return search(key)!=NULL ? true: false;
}

/*
 * Delete FibNode in the FibHeap
 */
void FibHeap::remove(FibNode *node)
{
    int m = min->key-1;
    decrease(node, m-1);
    removeMin();
}

void FibHeap::remove(int id)
{
    FibNode *node;
    if (min==NULL){
        cout << "removeNodeError: there is no node in the FibHeap" << endl;
        return;
    }
    node = idSearch(id);
    if (node==NULL)
        return;
    remove(node);
    return;
}

void FibHeap::remove(Record* record) {
    FibNode *node;
    if (min==NULL) {
        cout << "removeNodeError: there is no node in the FibHeap" << endl;
        return;
    }
    node = recordSearch(record);
    if (node==NULL)
        return;
    remove(node);
    return;
}

/*
 * Destroy FibHeap.
 */
void FibHeap::destroyNode(FibNode *node)
{
    FibNode *start = node;
    if(node == NULL)
        return;
    do {
        destroyNode(node->child);
        // 销毁node，并将node指向下一个
        node = node->right;
        delete node->left;
    } while(node != start);
    return;
}

void FibHeap::destroy()
{
    destroyNode(min);
    free(cons);
    return;
}


/*
 * Print "Fibonacci pile"
 *
 * Parameter Description:
 * Node --       current node
 * Prev --       the previous node of the current node (parent node or sibling node)
 * Direction --  1, indicating that the current node is a left child;
 *               2. Indicates that the current node is a sibling node.
 */
void FibHeap::print(FibNode *node, FibNode *prev, int direction)
{
    FibNode *start=node;
    if (node==NULL)
        return ;
    do
    {
        if (direction == 1)
            cout << setw(8) << node->record->getRecordID() << "(" << node->degree << ") is "<< setw(2) << prev->record->getRecordID()<< "'s child" << endl;
        else
            cout << setw(8) << node->record->getRecordID() << "(" << node->degree << ") is "<< setw(2) << prev->record->getRecordID() << "'s next" << endl;
        if (node->child != NULL)
            print(node->child, node, 1);
        prev = node;
        node = node->right;
        direction = 2;
    } while(node != start);
}

void FibHeap::print()
{
    if (min == NULL){
        cout << "PrintError: no node in the heap."<< endl;
        return;
    }
    int i = min->record->getRecordID();
    FibNode *p;
    if (min==NULL)
        return ;
    cout << "== Detailed Information in the FibHeap: ==" << endl;
    p = min;
    do {
        i = p->record->getRecordID();
        cout << setw(2) << i << ". " << setw(4) << p->record->getRecordID() << "(" << p->degree << ") is root" << endl;
        print(p->child, p, 1);
        p = p->right;
    } while (p != min);
    cout << endl;
}