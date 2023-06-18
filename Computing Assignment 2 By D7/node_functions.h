#pragma once
// Multiple head file only include once

// Include libraries

// Include our head files
#include "FibNode.h"
#include "ListNode.h"

/*=================================*
 * Function: major_priority
 * Created by Peidong Yang
 *---------------------
 * compare two node for priority
 *==================================*/
bool major_prior(FibNode* node1, FibNode* node2);

/*=================================*
 * Function: ddl_priority
 * Created by Peidong Yang
 *---------------------
 *   compare two node for priority
 * in ddl heap;
 *==================================*/
bool ddl_prior(FibNode* node1, FibNode* node2);


/*=================================*
 * Function: toListNode
 * Created by CYTIN
 *-----------------------------
 *   Use the Fibnode to get a
 * Listnode with same record;
 *==================================*/
ListNode* toListNode(FibNode* fibnode);

bool major_prior(FibNode* node1, FibNode* node2)
{
    if ((*node1).getKey() > (*node2).getKey())
        return true;
    else
        return false;
}

bool ddl_prior(FibNode* node1, FibNode* node2)
{
    return major_prior(node1,node2);
}

ListNode* toListNode(FibNode* fibnode)
{
    ListNode* ptr = new ListNode;
    (*ptr).setRecord((*fibnode).getRecord());
    //cout << (*ptr).getDummyBool() << endl;
    return ptr;
}
