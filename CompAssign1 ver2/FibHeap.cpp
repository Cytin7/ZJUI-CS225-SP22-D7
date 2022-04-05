//
// Created by FDChick on 2022/4/4.
//
#include <iostream>
#include "head.h"
#include <ctime>
using namespace std;

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