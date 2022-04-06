//created by Yang Peidong 2022/04/04
//
#include <stdio.h>
#include <iostream>
#include "head.h"
#include <cstdlib>
#include <ctime>
using std::cout;
using std::cin;



void FibNode::calc_priority_number()
//The most important criterion is the profession category followed by a ranking of age groups,
//and further followed by data and time of the registration.
//priority_number is an integer 
//position:    6           5         4 3     2 1
//meaning:profession   age_group    month    day
{
    struct tm *info;
    info = gmtime(&(this->reg_time));
    int month = info->tm_mon;
    int day = info->tm_mday;
    this->priority_number = (this->profession) * 100000 + (this->age_group) * 10000 + month * 100 + day * 1;
}

bool FibHeap::withdraw(FibNode *withdraw_node, FibHeap* main_heap1, FibHeap* main_heap2, FibHeap* withdraw_heap)
//this function is used to withdraw one node
//it removes the node out of main heap, and then insert it into withdraw heap
//INPUT: ptr of the node to be withdrawn, 2 main heaps, withdraw heap
//OUTPUT: true: withdraw successfully; false: withdraw unsuccessfully
//ATTENTION: this function will not return false
{
    main_heap1->remove(withdraw_node);
    main_heap2->remove(withdraw_node);
    withdraw_heap->Insert(withdraw_node);
    return true;
}

bool FibHeap::modify(FibNode *modified_node, int information_type, int new_information, 
                    FibHeap* main_heap1, FibHeap* main_heap2, FibHeap* medium_risk_heap, FibHeap* high_risk_heap, FibHeap* withdraw_heap)
//this function is used to modify information of one node and renew the priority of the node in the heap
//INPUT: ptr of modified node, information_type (1: risk status; 2: profession category), new information, 5 heaps.
//OUTPUT: true: modify successfully; false: type a wrong information type or type information out of range
//ATTENTION: this function judges the condition (that the new information is teh same as the present information) as success
{
    //INFORMATION TYPE 1: risk
    if (information_type == 1)   //risk(0-1: no or low risk; 2: medium risk; 3: high risk)
    {
        if (new_information > 3 && new_information < 0)  //information out of range
        {
            return false;
        }
        if (new_information == modified_node->getRecordRisk())  //new risk is the same as present risk
        {
            return true;
        }
        modified_node->setRecordRisk(new_information);   //modify the information
        //modify the risk means we may move the node to another heap
        //status means the current heap (0: Main heap; 1: high risk heap; 2: medium risk heap; 3: withdraw heap)
        //there are 7 conditions in total:
        //1. low->medium   2. low->high   3. medium->low   4. medimu->high   5. high->low   6. high->medium
        //7. the node is in withdraw heap, so we do not move the node
        if (modified_node->status == 0 && new_information == 2)
        {//1. low->medium: main heap->medium risk heap
            main_heap1->remove(modified_node);
            main_heap2->remove(modified_node);
            medium_risk_heap->Insert(modified_node);
            modified_node->status = 2;
            return true;
        }else if (modified_node->status == 0 && new_information == 3)
        {//2. low->high: main heap->high risk heap
            main_heap1->remove(modified_node);
            main_heap2->remove(modified_node);
            high_risk_heap->Insert(modified_node);
            modified_node->status = 1;
            return true;
        }else if (modified_node->status == 2 && (new_information == 0) || (new_information == 1)) 
        {//3. medium->low: medium risk heap->main heap
            medium_risk_heap->remove(modified_node);
            main_heap1->Insert(modified_node);
            main_heap2->Insert(modified_node);
            modified_node->status = 0;
            return true;
        }else if (modified_node->status == 2 && new_information == 3)
        {//4. medium->high: medium risk heap->high risk heap
            medium_risk_heap->remove(modified_node);
            high_risk_heap->Insert(modified_node);
            modified_node->status = 1;
            return true;
        }else if (modified_node->status == 1 && (new_information == 0) || (new_information == 1)) 
        {//5. high->low: high risk heap->main heap
            high_risk_heap->remove(modified_node);
            main_heap1->Insert(modified_node);
            main_heap2->Insert(modified_node);
            modified_node->status = 0;
            return true;
        }else if (modified_node->status == 1 && new_information == 2)
        {//6. high->meidum: high risk heap->medium risk heap
            high_risk_heap->remove(modified_node);
            medium_risk_heap->Insert(modified_node);
            modified_node->status = 2;
            return true;
        }else if (modified_node->status == 3)
        {//7. the node is in withdraw heap, so we do not move the node
            return true;
        }
    }
    //INFORMATION TYPE 2: profession
    else if (information_type == 2)
    {
        if (new_information > 7 && new_information < 0)  //information out of range
        {
            return false;
        }
        if (new_information == modified_node->getRecordProfession()) //new profession is the same as present profession
        {
            return true;
        }
        modified_node->setRecordProfession(new_information);//modify the information
        int temp = modified_node->get_priority_number();
        modified_node->calc_priority_number();   //renew the priority
        if (modified_node->status == 0)
        {//1. the node is in main heap, we need to heapify because the priority changes
            main_heap1->update(modified_node, temp);   //NEED TO BE CONFIRMED
            main_heap2->update(modified_node, temp);
            return true;
        }else
        {//2. the node is in other heaps, the priority is not relavent to priority number
            return true;
        }
    }
    //INFORMATION TYPE is wrong
    else
    {
        return false;
    }
}



FibNode* FibHeap::find_node(int id, FibHeap* main_heap, FibHeap* medium_risk_heap, FibHeap* high_risk_heap, FibHeap* withdraw_heap)
//this function is to find the node with identification id. 
//INPUT: id; main_heap; medium_risk_heap; high_risk_heap; withdraw_heap; 
//OUTPUT: ptr of FibNode (the corresponding node) OR NULL (no such node with identification id in any heap)
//ATTENTION: 
{
    if (main_heap->idsearch(id) != NULL)                      //the node is in main heap
    {
        return main_heap->idsearch(id);
    }else                                                     //the node is not in main heap
    {
        if (medium_risk_heap->idsearch(id) != NULL)           //the node is in medium risk heap
        {
            return medium_risk_heap->idsearch(id);
        }else
        {
            if (high_risk_heap->idsearch(id) != NULL)         //the node is in high risk heap
            {
                return high_risk_heap->idsearch(id);
            }else
            {
                if (withdraw_heap->idsearch(id) != NULL)      //the node is in withdraw heap
                {
                    return withdraw_heap->idsearch(id);
                }else                                         //the node is not in any heap, return NULL
                {
                    return NULL;
                }
            }
        }
    }
}