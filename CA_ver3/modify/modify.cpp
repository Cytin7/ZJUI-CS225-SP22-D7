#include "modify.h"

//created by Yang Peidong 2022/04/07
//


void modify_operation(int modified_id, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* medium_risk_heap, FibHeap* high_risk_heap, FibHeap* withdraw_heap)
{
	FibNode* modified_node_ddl = ddl_heap->idsearch(ddl_heap->getMin(), modified_id);
	FibNode* modified_node_main = main_heap->idsearch(main_heap->getMin(), modified_id);
	FibNode* modified_node_medium = medium_risk_heap->idsearch(medium_risk_heap->getMin(), modified_id);
	FibNode* modified_node_high = high_risk_heap->idsearch(high_risk_heap->getMin(), modified_id);
	FibNode* modified_node_withdraw = withdraw_heap->idsearch(withdraw_heap->getMin(), modified_id);
	//1. the node is not in any heap
	if (modified_node_ddl == NULL && modified_node_main == NULL && modified_node_medium == NULL &&
		modified_node_high == NULL && modified_node_withdraw == NULL)
	{
		cout << "There is no such patient with identificaltion " << modified_id << " in all heaps.\n";
		return;
	}
	//2. the node is in ddl and main heap
	else if (modified_node_ddl != NULL && modified_node_main != NULL)
	{
		cout << "The patient with identification " << modified_id << " is in main and ddl heap.\n";
		bool x = modify_for_main_and_ddl(modified_node_ddl, modified_node_main, information_type, new_information,
			ddl_heap, main_heap, medium_risk_heap, high_risk_heap);
		if (x) //modify_for_main_and_ddl(...) returns true
		{
			cout << "Modify the information of the patient with identification " << modified_id << " succcessfully.\n";
			if (information_type == 1)//2. modify risk
			{
				cout << "Specifically, risk status: " << modified_node_ddl->getRecordRisk() << "->" << new_information << ".\n";
			}
			else if (information_type == 2)//3. modify profession
			{
				cout << "Specifically, profession category: " << modified_node_ddl->getRecordProfession() << "->" << new_information << ".\n";
			}
		}
		else  //modify unsuccessfully
		{
			cout << "The new information is out of range.\n";
		}
	}
	//3. the node is in medium risk heap
	else if (modified_node_medium != NULL)
	{
		cout << "The patient with identification " << modified_id << " is in medium risk heap.\n";
		bool y = modify_for_medium_risk(modified_node_medium, information_type, new_information,
			ddl_heap, main_heap, high_risk_heap);
		if (y) //modify_for_medium_risk(...) returns true
		{
			cout << "Modify the information of the patient with identification " << modified_id << " succcessfully.\n";
			if (information_type == 1)//2. modify risk
			{
				cout << "Specifically, risk status: " << modified_node_medium->getRecordRisk() << "->" << new_information << ".\n";
			}
			else if (information_type == 2)//3. modify profession
			{
				cout << "Specifically, profession category: " << modified_node_medium->getRecordProfession() << "->" << new_information << ".\n";
			}
		}
		else  //modify unsuccessfully
		{
			cout << "You may type a wrong information type or the new information is out of range.\n";
		}
	}
	//4. the node is in high risk heap
	else if (modified_node_high != NULL)
	{
		cout << "The patient with identification " << modified_id << " is in high risk heap.\n";
		bool z = modify_for_high_risk(modified_node_high, information_type, new_information,
			ddl_heap, main_heap, medium_risk_heap);
		if (z) //modify_for_medium_risk(...) returns true
		{
			cout << "Modify the information of the patient with identification " << modified_id << " succcessfully.\n";
			if (information_type == 1)//2. modify risk
			{
				cout << "Specifically, risk status: " << modified_node_high->getRecordRisk() << "->" << new_information << ".\n";
			}
			else if (information_type == 2)//3. modify profession
			{
				cout << "Specifically, profession category: " << modified_node_high->getRecordProfession() << "->" << new_information << ".\n";
			}
		}
		else  //modify unsuccessfully
		{
			cout << "You may type a wrong information type or the new information is out of range.\n";
		}
	}
	//5. the node is in withdraw heap
	else if (modified_node_withdraw != NULL)
	{
		cout << "The patient with identification " << modified_id << " is in withdraw heap.\n";
		bool w = modify_for_withdraw(modified_node_withdraw, information_type, new_information);
		if (w) //modify_for_withdraw(...) returns true
		{
			cout << "Modify the information of the patient with identification " << modified_id << " succcessfully.\n";
			if (information_type == 1)//2. modify risk
			{
				cout << "Specifically, risk status: " << modified_node_withdraw->getRecordRisk() << "->" << new_information << ".\n";
			}
			else if (information_type == 2)//3. modify profession
			{
				cout << "Specifically, profession category: " << modified_node_withdraw->getRecordProfession() << "->" << new_information << ".\n";
			}
		}
		else  //modify unsuccessfully
		{
			cout << "You may type a wrong information type or the new information is out of range.\n";
		}
	}
	//it should have been only 5 conditions above.
	else
	{
		cout << "WRONG PROCESS!!!\n";
	}
}


bool modify_for_main_and_ddl(FibNode* node_ddl, FibNode* node_main, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* medium_risk_heap, FibHeap* high_risk_heap)
	//the node is in main and ddl heap (risk = 0-1)
	//0 - main_heap; 1 - ddl_heap; 2 - medium_risk_heap; 3 - high_risk_heap; 4 - withdraw_heap;
	//remove processing: 1. remove; 2. update information; 3. update status; 4. re-calculate priority; 5. insert
{
	//modify risk(0-3)
	//1. new infromation = old information, do nothing
	//2. new information = 0-1, the node will not be moved, since it will be also in main and ddl heap
	//3. new information = 2-3, the node will be moved
	if (information_type == 1)
	{
		if (new_information == node_ddl->getRecordRisk()) //new information = old information
		{
			return true;
		}
		if (new_information == 0 || new_information == 1)  //also in main and ddl heap
		{
			node_ddl->setRecordRisk(new_information);
			node_main->setRecordRisk(new_information);
			return true;
		}
		else if (new_information == 2)  //move in medium risk heap
		{//we remove the 2 nodes out of main and ddl heap, and then move node_main into medium risk heap
			ddl_heap->remove(node_ddl);
			main_heap->remove(node_main);
			node_main->setRecordRisk(new_information);
			node_main->status = 2;
			node_main->calc_priority_number();
			medium_risk_heap->Insert(node_main);
			return true;
		}
		else if (new_information == 3)  //move in high risk heap
		{//we remove the 2 nodes out of main and ddl heap, and then move node_main into high risk heap
			ddl_heap->remove(node_ddl);
			main_heap->remove(node_main);
			node_main->setRecordRisk(new_information);
			node_main->status = 3;
			node_main->calc_priority_number();
			high_risk_heap->Insert(node_main);
			return true;
		}
		else  //new information out of range
		{
			return false;
		}
	}
	//modify profession category(0-7)
	//we do not need to move any node into another heap, but we should update the priority of node main
	else if (information_type == 2)
	{
		if (new_information >= 0 && new_information <= 7) //new information in range
		{
			node_ddl->setRecordProfession(new_information);
			node_main->setRecordProfession(new_information);
			int temp = node_main->get_priority_number();  //update the priority of main/*******WHAT IS THE UEASG OF THE FUNCTION
			node_main->calc_priority_number();
			main_heap->update(node_main, temp);
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

bool modify_for_medium_risk(FibNode* node_medium, int information_type, int new_information,
	FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* high_risk_heap)
	//the node is in medium risk heap
{
	//modify risk(0-3)
	//1. new information = old information, do nothing
	//2. new information = 0-1, the node will be moved into main and ddl heap, here we need to create a new node
	//3. new information = 3, the node will be moved into high risk heap
	if (information_type == 1)
	{
		if (new_information == node_medium->getRecordRisk()) //new information = old information
		{
			return true;
		}
		if (new_information == 0 || new_information == 1) //move medium node into main heap, insert the new node into ddl heap
		{
			node_medium->setRecordRisk(new_information);
			FibNode* new_node_ddl = new FibNode;//we do not use new
			*new_node_ddl = *node_medium;   //copy all information******DEEP COPY OR SHALLOW COPY???
			node_medium->status = 0; //0 - main heap
			node_medium->calc_priority_number();
			main_heap->Insert(node_medium);
			new_node_ddl->status = 1; //1 - ddl heap
			new_node_ddl->calc_priority_number();
			ddl_heap->Insert(new_node_ddl);
			return true;
		}
		else if (new_information == 3)  //move the node into high risk heap
		{
			node_medium->setRecordRisk(new_information);
			node_medium->status = 3; //3 - high risk heap
			node_medium->calc_priority_number();
			main_heap->Insert(node_medium);
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
			node_medium->setRecordProfession(new_information);
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
	FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* medium_risk_heap)
	//the node is in high risk heap
{
	//modify risk(0-3)
	//1. new information = old information, do nothing
	//2. new information = 0-1, the node will be moved into main and ddl heap, here we need to create a new node
	//3. new information = 2, the node will be moved into medium risk heap
	if (information_type == 1)
	{
		if (new_information == node_high->getRecordRisk()) //new information = old information
		{
			return true;
		}
		if (new_information == 0 || new_information == 1) //move node_high into main heap, insert the new node into ddl heap
		{
			node_high->setRecordRisk(new_information);
			FibNode* new_node_ddl = new FibNode;
			*new_node_ddl = *node_high;   //copy all information******DEEP COPY OR SHALLOW COPY???
			node_high->status = 0; //0 - main heap
			node_high->calc_priority_number();
			main_heap->Insert(node_high);
			new_node_ddl->status = 1; //1 - ddl heap
			new_node_ddl->calc_priority_number();
			ddl_heap->Insert(new_node_ddl);
			return true;
		}
		else if (new_information == 2)  //move the node into high risk heap
		{
			node_high->setRecordRisk(new_information);
			node_high->status = 2; //3 - medium risk heap
			node_high->calc_priority_number();
			main_heap->Insert(node_high);
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
			node_high->setRecordProfession(new_information);
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

bool modify_for_withdraw(FibNode* node_withdraw, int information_type, int new_information)
//the node is in withdraw heap
{
	//modify risk(0-3)
	//we only need to update the information
	if (information_type == 1)
	{
		if (new_information >= 0 && new_information <= 3)  //new information in range
		{
			node_withdraw->setRecordRisk(new_information);
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
			node_withdraw->setRecordProfession(new_information);
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