#pragma once
#include "Tree.h"
/*************************************Scheduling classes****************************************/
//Scheduling class, according to the parameters passed in, select a specific policy


// Notice:
// The main body of BTree code is originated from "orange1438",
// his github repository ：BTree and BPlusTree Realize
// Link: https://github.com/orange1438/BTree-and-BPlusTree-Realize
// Due to the limit of time, our code is the modified version of it
// And applying to the CA2 project
// The program is based on Windows System

class Context 
{
private:
	Tree *strategyChild;
public:
	Context(Tree *child)
 	{
		strategyChild=child;
	}

	void Insert(int target)
 	{
		strategyChild->insert(target);
	}
	void LevelDisplay()
	{
		strategyChild->level_display();
	};
	
	void Del(int target)
	{
		strategyChild->del(target);
	};
	
	void Inorder_Print()
	{
		strategyChild->inorder_print();
	};
	
	// tree node num
	void NodeNum_Print()
	{
		strategyChild->NodeNum_print();
	};
};
