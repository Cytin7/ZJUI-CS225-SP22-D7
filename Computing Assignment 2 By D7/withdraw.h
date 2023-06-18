//created by Yang Peidong 2022/04/07
//
#include <stdio.h>
#include <iostream>
#include "FibHeap.h"
#include "FibNode.h"
#include <cstdlib>
#include <ctime>
#include "node_functions.h"

using std::cout;
using std::cin;

void withdraw_operation(int withdraw_id, FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* hr_heap, ListNode* withdraw_list, ListNode* medium_risk_list, time_t current_time);


void withdraw_operation(int withdraw_id, FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* hr_heap, ListNode* withdraw_list, ListNode* medium_risk_list, time_t current_time)
//this function includes all operations of modifying. it will print out relavent information in terms of the input
//we have 4 possible situations:
//1. we do not find the node in main heap (and ddl heap). it may in other heaps or not in any heap, but we do not care;
//2. the node is in main/ddl heap (move it into withdraw heap);
//ATTENTION: the change of status has been executed in function withdraw(...)
//NEW: main heap has all normal nodes, but ddl heap only has the nodes with a ddl
{
    FibNode* withdraw_node1 = ddl_heap->idSearch(withdraw_id);
    FibNode* withdraw_node2 = main_heap->idSearch(withdraw_id);
    FibNode* withdraw_node3 = hr_heap->idSearch(withdraw_id);
    ListNode* withdraw_node4 = medium_risk_list->idsearch(withdraw_id);

    if (withdraw_node2 != nullptr)  //1. find the node in main heap
    {
        if ( withdraw_node1 != nullptr ) {
            ddl_heap->remove(withdraw_id);
            main_heap->remove(withdraw_id);
            ListNode *withdraw_node;                   //FibNode -> ListNode
            withdraw_node = toListNode(withdraw_node1);
            withdraw_node->getRecord()->reg_time = current_time;
            withdraw_list->insert(withdraw_node);
            withdraw_node->getRecord()->status = 3;
            cout << "Withdraw the patient with identification " << withdraw_id << " successfully.\n";
            return;
        }//3. the node has not a ddl(only in the main heap), we withdraw it and move it into withdraw list
        else if ( withdraw_node1 == nullptr ) {
            main_heap->remove(withdraw_id);
            ListNode *withdraw_node;                   //FibNode -> ListNode
            withdraw_node = toListNode(withdraw_node2);
            withdraw_list->insert(withdraw_node);
            withdraw_node->getRecord()->status = 3;
            cout << "Withdraw the patient with identification " << withdraw_id << " successfully.\n";
            return;
        } else {
            cout << "WRONG PRECESS!!!\n";
        }
    }
    else if ( withdraw_node3 != nullptr ) {
        hr_heap->remove(withdraw_id);
        ListNode* withdraw_node;
        withdraw_node = toListNode(withdraw_node1);
        withdraw_node->getRecord()->reg_time = current_time;
        withdraw_list->insert(withdraw_node);
        withdraw_node->getRecord()->status = 3;
        cout << "Withdraw the patient with identification " << withdraw_id << " successfully.\n";
        return;
    }
    else if ( withdraw_node4 != nullptr ) {
        ListNode* withdraw_node;
        withdraw_node = medium_risk_list->remove(withdraw_node4);
        withdraw_node->getRecord()->reg_time = current_time;
        withdraw_list->insert(withdraw_node);
        withdraw_node->getRecord()->status = 3;
        cout << "Withdraw the patient with identification " << withdraw_id << " successfully.\n";
        return;
    }
    else{
        cout << "WithdrawError: Node to withdraw not found. id = " << withdraw_id <<  "." <<endl;
    }
    return;
}