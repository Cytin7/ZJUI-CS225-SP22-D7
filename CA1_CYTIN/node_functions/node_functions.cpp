#include "node_functions.h"

/*=================================*
 * Function: major_priority
 * Created by Peidong Yang
 * Improved by Cytin
 *---------------------
 *   compare two node for priority
 * in main heap and high risk heap
 *==================================*/
bool major_prior(FibNode* node1, FibNode* node2)
{
	Record r1 = *(*node1).getRecord();
	Record r2 = *(*node2).getRecord();
	if (r1.getRecordProfession() < r2.getRecordProfession()) {
		return true;
	}
	else if (r1.getRecordProfession() > r2.getRecordProfession()) {
		return false;
	}
	// if profession same, compare age group
	if (r1.getRecordAgeGroup() < r2.getRecordAgeGroup()) {
		return true;
	}
	else if (r1.getRecordAgeGroup() > r2.getRecordAgeGroup()) {
		return false;
	}
	// if still same, compare regist time
	if (r1.getRecordRegisterTime() < r2.getRecordRegisterTime()) {
		return true;
	}
	else {
		return false;
	}
}

/*=================================*
 * Function: ddl_priority
 * Created by Peidong Yang
 *---------------------
 *   compare two node for priority
 * in ddl heap;
 *==================================*/
bool ddl_prior(FibNode* node1, FibNode* node2)
{
	Record r1 = *(*node1).getRecord();
	Record r2 = *(*node2).getRecord();
	if (r1.getRecordDeadline() < r2.getRecordDeadline()) {
		return true;
	}
	else
	{
		return false;
	}
}

/*=================================*
 * Function: toListNode
 * Created by CYTIN
 *-----------------------------
 *   Use the Fibnode to get a
 * Listnode with same record;
 *==================================*/
ListNode* toListNode(FibNode* fibnode)
{
	ListNode* ptr = new ListNode;
	(*ptr).setRecord((*fibnode).getRecord());
	//cout << (*ptr).getDummyBool() << endl;
	return ptr;
}
