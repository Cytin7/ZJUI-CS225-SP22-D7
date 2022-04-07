//created by Yang Peidong 2022/04/07
//
#include <stdio.h>
#include <iostream>
#include "../head.h"
#include <cstdlib>
#include <ctime>
using std::cout;
using std::cin;

void withdraw_operation(int withdraw_id, FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* withdraw_heap)
//this function includes all operations of modifying. it will print out relavent information in terms of the input
//we have 4 possible situations:
//1. we do not find the node in main heap (and ddl heap). it may in other heaps or not in any heap, but we do not care;
//2. the node is in main/ddl heap (move it into withdraw heap);
//ATTENTION: the change of status has been executed in function withdraw(...)
{
    FibNode* withdraw_node1 = ddl_heap->idsearch(withdraw_id);
    FibNode* withdraw_node2 = main_heap->idsearch(withdraw_id);
    if (withdraw_node1 == NULL && withdraw_node2 == NULL)  //1. does not find the node in main heap (ddl heap)
    {
        cout<<"There is no such patient with identification "<<withdraw_id<<" in main heaps. \n";
        return;
    }//2. the node is in the main and ddl heap, we withdraw it separately and move one into withdraw heap
    else if (withdraw_node1 != NULL && withdraw_node2 != NULL)
    {
        ddl_heap->remove(withdraw_node1);
        main_heap->remove(withdraw_node2);
        withdraw_heap->Insert(withdraw_node1);
        cout<<"Withdraw the patient with identification "<<withdraw_id<<" successfully.\n";
        return;
    }
    else
    {
        cout<<"WRONG PRECESS!!!\n";
    }
}