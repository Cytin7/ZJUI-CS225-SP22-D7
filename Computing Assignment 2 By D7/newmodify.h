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

void modify_operation(int modified_id, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap, ListNode* withdraw_list);

bool modify_for_main_and_ddl(FibNode* node_ddl, FibNode* node_main, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap);

bool modify_for_main(FibNode* node_main, int information_type, int new_information,
	FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap);

bool modify_for_medium_risk(ListNode* node_medium, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap);

bool modify_for_high_risk(FibNode* node_high, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap);

bool modify_for_withdraw(ListNode* node_withdraw, int information_type, int new_information);



void modify_operation(int modified_id, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap, ListNode* withdraw_list)
{
	FibNode* modified_node_ddl = ddl_heap->idSearch(modified_id);
	FibNode* modified_node_main = main_heap->idSearch(modified_id);
	ListNode* modified_node_medium = medium_risk_list->idsearch(modified_id);
	FibNode* modified_node_high = high_risk_heap->idSearch(modified_id);
	ListNode* modified_node_withdraw = withdraw_list->idsearch(modified_id);
	//1. the node is not in any heap
	if (modified_node_ddl == NULL && modified_node_main == NULL && modified_node_medium == NULL &&
		modified_node_high == NULL && modified_node_withdraw == NULL)
	{
		cout << "There is no such patient with identification " << modified_id << " in all heaps.\n";
		return;
	}
	//2. the node is in ddl and main heap (normal node with a ddl)
	else if (modified_node_ddl != NULL && modified_node_main != NULL)
	{
		cout << "The patient with identification " << modified_id << " is in main and ddl heap.\n";
        Record* temp = modified_node_main->record;
		bool x = modify_for_main_and_ddl(modified_node_ddl, modified_node_main, information_type, new_information,
			ddl_heap, main_heap, medium_risk_list, high_risk_heap);
		if (x) //modify_for_main_and_ddl(...) returns true
		{
			cout << "Modify the information of the patient with identification " << modified_id << " successfully.\n";
			if (information_type == 1)//2. modify risk
			{
				cout << "Specifically, risk status: " << temp->getRecordRisk() << "->" << new_information << ".\n";
			}
			else if (information_type == 2)//3. modify profession
			{
				cout << "Specifically, profession category: " << temp->getRecordProfession() << "->" << new_information << ".\n";
			}
		}
		else  //modify unsuccessfully
		{
			cout << "The new information is out of range.\n";
		}
	}
	//3. the node is in main heap (normal node without a ddl)
	else if (modified_node_ddl == NULL && modified_node_main != NULL)
	{
		cout << "The patient with identification " << modified_id << " is in main heap, not in ddl heap.\n";
        Record* temp = modified_node_main->record;
		bool x = modify_for_main(modified_node_main, information_type, new_information,
			main_heap, medium_risk_list, high_risk_heap);
		if (x) //modify_for_main_and_ddl(...) returns true
		{
			cout << "Modify the information of the patient with identification " << modified_id << " successfully.\n";
			if (information_type == 1)//2. modify risk
			{
				cout << "Specifically, risk status: " << temp->getRecordRisk() << "->" << new_information << ".\n";
			}
			else if (information_type == 2)//3. modify profession
			{
				cout << "Specifically, profession category: " << temp->getRecordProfession() << "->" << new_information << ".\n";
			}
		}
		else  //modify unsuccessfully
		{
			cout << "The new information is out of range.\n";
		}
	}
	//4. the node is in medium risk list
	else if (modified_node_medium != NULL)
	{
		cout << "The patient with identification " << modified_id << " is in medium risk heap.\n";
        Record* temp = modified_node_medium->getRecord();
		bool y = modify_for_medium_risk(modified_node_medium, information_type, new_information,
			ddl_heap, main_heap, medium_risk_list, high_risk_heap);
		if (y) //modify_for_medium_risk(...) returns true
		{
			cout << "Modify the information of the patient with identification " << modified_id << " successfully.\n";
			if (information_type == 1)//2. modify risk
			{
				cout << "Specifically, risk status: " << temp->getRecordRisk() << "->" << new_information << ".\n";
			}
			else if (information_type == 2)//3. modify profession
			{
				cout << "Specifically, profession category: " << temp->getRecordProfession() << "->" << new_information << ".\n";
			}
		}
		else  //modify unsuccessfully
		{
			cout << "You may type a wrong information type or the new information is out of range.\n";
		}
	}
	//5. the node is in high risk heap
	else if (modified_node_high != NULL)
	{
		cout << "The patient with identification " << modified_id << " is in high risk heap.\n";
        Record* temp = modified_node_high->record;
		bool z = modify_for_high_risk(modified_node_high, information_type, new_information,
			ddl_heap, main_heap, medium_risk_list, high_risk_heap);
		if (z) //modify_for_medium_risk(...) returns true
		{
			cout << "Modify the information of the patient with identification " << modified_id << " successfully.\n";
			if (information_type == 1)//2. modify risk
			{
				cout << "Specifically, risk status: " << temp->getRecordRisk() << "->" << new_information << ".\n";
			}
			else if (information_type == 2)//3. modify profession
			{
				cout << "Specifically, profession category: " << temp->getRecordProfession() << "->" << new_information << ".\n";
			}
		}
		else  //modify unsuccessfully
		{
			cout << "You may type a wrong information type or the new information is out of range.\n";
		}
	}
	//6. the node is in withdraw heap
	else if (modified_node_withdraw != NULL)
	{
		cout << "The patient with identification " << modified_id << " is in withdraw heap.\n";
        Record* temp = modified_node_withdraw->getRecord();
		bool w = modify_for_withdraw(modified_node_withdraw, information_type, new_information);
		if (w) //modify_for_withdraw(...) returns true
		{
			cout << "Modify the information of the patient with identification " << modified_id << " succcessfully.\n";
			if (information_type == 1)//2. modify risk
			{
				cout << "Specifically, risk status: " << temp->getRecordRisk() << "->" << new_information << ".\n";
			}
			else if (information_type == 2)//3. modify profession
			{
				cout << "Specifically, profession category: " << temp->getRecordProfession() << "->" << new_information << ".\n";
			}
		}
		else  //modify unsuccessfully
		{
			cout << "You may type a wrong information type or the new information is out of range.\n";
		}
	}
	//it should have been only 6 conditions above.
	else
	{
		cout << "WRONG PROCESS!!!\n";
	}
}


bool modify_for_main_and_ddl(FibNode* node_ddl, FibNode* node_main, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap)
	//the node is in main and ddl heap (risk = 0-1 with a ddl)
	//1 - main_heap; 2 - ddl_heap; 3 - high_risk_heap;
	//remove processing: 1. remove; 2. update information; 3. update status; 4. re-calculate priority; 5. insert
{
	//modify risk(0-3)
	//1. new infromation = old information, do nothing
	//2. new information = 0-1, the node will not be moved, since it will be also in main and ddl heap
	//3. new information = 2-3, the node will be moved
	if (information_type == 1)
	{
		if (new_information == node_ddl->record->getRecordRisk()) //new information = old information
		{
			return true;
		}
		if (new_information == 0 || new_information == 1)  //also in main and ddl heap
		{
			node_ddl->record->setRecordRisk(new_information);
			node_main->record->setRecordRisk(new_information);
			return true;
		}
		else if (new_information == 2)  //move in medium risk list(FibNode->ListNode)
		{//we remove the 2 nodes out of main and ddl heap, and then move node_main into medium risk heap
			ddl_heap->remove(node_ddl);
			main_heap->remove(node_main);
			ListNode* new_medium_node;
			new_medium_node = toListNode(node_ddl);      //change type
			new_medium_node->getRecord()->setRecordRisk(new_information);
			medium_risk_list->insert(new_medium_node);
			return true;
		}
		else if (new_information == 3)  //move in high risk heap
		{//we remove the 2 nodes out of main and ddl heap, and then move node_main into high risk heap
			ddl_heap->remove(node_ddl);
			main_heap->remove(node_main);
			node_main->record->setRecordRisk(new_information);
			node_main->setType(3);
			node_main->calcKey();
			high_risk_heap->insert(node_main);
			return true;
		}
		else  //new information out of range
		{
			return false;
		}
	}
	//modify profession category(0-7)
	//we do not need to move any node into another heap, but we should update the priority of node main(remove then insert)
	else if (information_type == 2)
	{
		if (new_information >= 0 && new_information <= 7) //new information in range
		{
			main_heap->remove(node_main);
			node_ddl->record->setRecordProfession(new_information);
			node_main->record->setRecordProfession(new_information);
			node_main->calcKey();
			main_heap->insert(node_main);
			return true;
		}
		else //new information out of range
		{
			return false;
		}
	}
	//wrong information type
	else
	{
		return false;
	}
}


bool modify_for_main(FibNode* node_main, int information_type, int new_information,
	FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap)
	//the node is in main heap (risk = 0-1 without a ddl)
	//0 - main_heap; 1 - ddl_heap; 2 - medium_risk_heap; 3 - high_risk_heap; 4 - withdraw_heap;
	//remove processing: 1. remove; 2. update information; 3. update status; 4. re-calculate priority; 5. insert
{
	//modify risk(0-3)
	//1. new infromation = old information, do nothing
	//2. new information = 0-1, the node will not be moved, since it will be also in main heap
	//3. new information = 2-3, the node will be moved
	if (information_type == 1)
	{
		if (new_information == node_main->record->getRecordRisk()) //new information = old information
		{
			return true;
		}
		if (new_information == 0 || new_information == 1)  //also in main heap
		{
			node_main->record->setRecordRisk(new_information);
            node_main->calcKey();
			return true;
		}
		else if (new_information == 2)  //move in medium risk list(FibNode->ListNode)
		{//we remove the node out of main heap, and then move node_main into medium risk list
			main_heap->remove(node_main);
			ListNode* new_medium_node;
			new_medium_node = toListNode(node_main);      //change type
			new_medium_node->getRecord()->setRecordRisk(new_information);
			medium_risk_list->insert(new_medium_node);
			return true;
		}
		else if (new_information == 3)  //move in high risk heap
		{//we remove the node out of main heap, and then move node_main into high risk heap
			main_heap->remove(node_main);
			node_main->record->setRecordRisk(new_information);
			node_main->type = 3;
			node_main->calcKey();
			high_risk_heap->insert(node_main);
			return true;
		}
		else  //new information out of range
		{
			return false;
		}
	}
	//modify profession category(0-7)
	//we do not need to move any node into another heap, but we should update the priority of node main(remove then insert)
	else if (information_type == 2)
	{
		if (new_information >= 0 && new_information <= 7) //new information in range
		{
			main_heap->remove(node_main);
			node_main->record->setRecordProfession(new_information);
			node_main->calcKey();
			main_heap->insert(node_main);
			return true;
		}
		else //new information out of range
		{
			return false;
		}
	}
	//wrong information type
	else
	{
		return false;
	}
}


bool modify_for_medium_risk(ListNode* node_medium, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap)
	//the node is in medium risk list
{
	//modify risk(0-3)
	//1. new information = old information, do nothing
	//2. new information = 0-1, the node will be moved into main heap(and ddl heap), here we need to create a new node
	//3. new information = 3, the node will be moved into high risk heap
	if (information_type == 1)
	{
		if (new_information == node_medium->getRecord()->getRecordRisk()) //new information = old information
		{
			return true;
		}
		if (new_information == 0 || new_information == 1) //move medium node into main heap (and ddl heap)
		{
			//the node has a ddl, we need to create a new node
			if (node_medium->getRecord()->getRecordDDLBool() == true)
			{
				node_medium->getRecord()->setRecordRisk(new_information);
				medium_risk_list->remove(node_medium);
                FibNode* new_main_node;
				new_main_node = node_medium->toFibNode(1);
				FibNode* new_ddl_node = new FibNode(2, node_medium->getRecord());
				new_main_node->calcKey();
				new_ddl_node->calcKey();
		    	main_heap->insert(new_main_node);
		    	ddl_heap->insert(new_ddl_node);
		    	return true;
			}
			//the node does not have a ddl
			else
			{
				node_medium->getRecord()->setRecordRisk(new_information);
				medium_risk_list->remove(node_medium);
                FibNode* new_main_node;
				new_main_node = node_medium->toFibNode(1);
				new_main_node->calcKey();
				main_heap->insert(new_main_node);
				return true;
			}
			
		}
		else if (new_information == 3)  //move the node into high risk heap
		{
			node_medium->getRecord()->setRecordRisk(new_information);
			medium_risk_list->remove(node_medium);
            FibNode* new_high_node;
			new_high_node = node_medium->toFibNode(3);
			new_high_node->calcKey();
			high_risk_heap->insert(new_high_node);
			return true;
		}
		else  //new information out of range
		{
			return false;
		}
	}
	//modify profession category(0-7)
	//we do not need to move any node into another heap, nor update the priority of the node
	else if (information_type == 2)
	{
		if (new_information >= 0 && new_information <= 7) //new information in range
		{
			node_medium->getRecord()->setRecordProfession(new_information);
			return true;
		}
		else //new information out of range
		{
			return false;
		}
	}
	//wrong information type
	else
	{
		return false;
	}
}

bool modify_for_high_risk(FibNode* node_high, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, ListNode* medium_risk_list, FibHeap* high_risk_heap)
	//the node is in high risk heap
{
	//modify risk(0-3)
	//1. new information = old information, do nothing
	//2. new information = 0-1, the node will be moved into main heap(and ddl heap)
	//3. new information = 2, the node will be moved into medium risk heap
	if (information_type == 1)
	{
		if (new_information == node_high->record->getRecordRisk()) //new information = old information
		{
			return true;
		}
		if (new_information == 0 || new_information == 1) //move node_high into main heap(and ddl heap)
		{
			//the node has a ddl, we need to create a new node
			if (node_high->getRecord()->getRecordDDLBool() == true)
			{
				high_risk_heap->remove(node_high);
				node_high->getRecord()->setRecordRisk(new_information);
				node_high->setType(1);
                node_high->calcKey();
				FibNode* new_ddl_node = new FibNode(2, node_high->getRecord());
		    	main_heap->insert(node_high);
		    	ddl_heap->insert(new_ddl_node);
		    	return true;
			}
			//the node does not have a ddl
			else
			{
				high_risk_heap->remove(node_high);
				node_high->getRecord()->setRecordRisk(new_information);
				node_high->setType(1);
                node_high->calcKey();
				main_heap->insert(node_high);
				return true;
			}
		}
		else if (new_information == 2)  //move the node into medium risk list
		{
			high_risk_heap->remove(node_high);
			ListNode* new_medium_node;
			new_medium_node = toListNode(node_high);
			new_medium_node->getRecord()->setRecordRisk(new_information);
			medium_risk_list->insert(new_medium_node);
			return true;
		}
		else  //new information out of range
		{
			return false;
		}
	}
	//modify profession category(0-7)
	//we do not need to move any node into another heap, nor update the priority of the node
	else if (information_type == 2)
	{
		if (new_information >= 0 && new_information <= 7) //new information in range
		{
			high_risk_heap->remove(node_high);
			node_high->record->setRecordProfession(new_information);
			node_high->calcKey();
			high_risk_heap->insert(node_high);
			return true;
		}
		else //new information out of range
		{
			return false;
		}
	}
	//wrong information type
	else
	{
		return false;
	}
}

bool modify_for_withdraw(ListNode* node_withdraw, int information_type, int new_information)
//the node is in withdraw heap
{
	//modify risk(0-3)
	//we only need to update the information
	if (information_type == 1)
	{
		if (new_information >= 0 && new_information <= 3)  //new information in range
		{
			node_withdraw->getRecord()->setRecordRisk(new_information);
			return true;
		}
		else  //new information out of range
		{
			return false;
		}
	}
	//modify profession category(0-7)
	else if (information_type == 2)
	{
		if (new_information >= 0 && new_information <= 7)  //new information in range
		{
			node_withdraw->getRecord()->setRecordProfession(new_information);
			return true;
		}
		else  //new information out of range
		{
			return false;
		}
	}
	//wrong information type
	else
	{
		return false;
	}
}