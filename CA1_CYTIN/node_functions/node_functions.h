#pragma once
// Multiple head file only include once

// Include libraries

// Include our head files
#include "../Class_FibNode/FibNode.h"
#include "../Class_ListNode/ListNode.h"

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