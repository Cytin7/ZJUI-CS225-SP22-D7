#include "head.h"
#include <fstream>



int main() {
	// record the current date for comparation
	//int current_year;
	int current_month;
	//int current_day;

	// store the number input
	int input_key = -1;     // main page key input
	int input_key2 = -1;    // seb page key input

	//current_year = gmtime(&current_time)->tm_year;
	current_month = gmtime(&current_time)->tm_mon;
	//current_year = gmtime(&current_time)->tm_year;

	//PNode<ListNode> registry_list;
	//registry_list.set_dummy();

	// Input file for registries
	fstream myfile1;
	myfile1.open("./Data/INPUT_00.csv");
	fstream myfile2;
	myfile2.open("./Data/INPUT_01.csv");
	fstream myfile3;
	myfile3.open("./Data/INPUT_02.csv");

	// Registries
	ListNode Reg1;
	ListNode Reg2;
	ListNode Reg3;
	Reg1.setDummy();
	Reg2.setDummy();
	Reg3.setDummy();
	Reg1.setCapacity(5);
	Reg2.setCapacity(5);
	Reg3.setCapacity(5);

	// Hospitals
	ListNode Hos1;
	ListNode Hos2;
	Hos1.setDummy();
	Hos2.setDummy();
	Hos1.setCapacity(7);
	Hos2.setCapacity(6);

	FibHeap* ddl_heap = new FibHeap;
	FibHeap* main_heap = new FibHeap;
	FibHeap* high_risk_heap = new FibHeap;
	FibHeap* medium_risk_heap = new FibHeap;
	FibHeap* withdraw_heap = new FibHeap;



	while (true)
	{
		input_key = PrintMainPage();
		switch (input_key)
		{
		case 0:
			// close the program
			cout << "The program is closed" << endl;
			// delete all heaps
			delete ddl_heap; // deadline
			delete main_heap; // priority
			delete high_risk_heap;
			delete medium_risk_heap;
			delete withdraw_heap;

			return 0;
			break;
		case 1:
		{
			// Show the registry setup menu.
			input_key2 = PrintRegistrySetupPage();
			switch (input_key2)
			{
			case 0:
				break;
			case 1:

				break;
			default:
				break;
			}
			break;
		}
		case 2:
		{
			// Show the hospital setup menu
			input_key2 = PrintHospitalSetupPage();
			switch (input_key2)
			{
			case 0:
				break;
			case 1:

				break;
			default:
				break;
			}
		}

		case 9:
		{
			// step in in half day
			// Part 1
			{
				// update current time
				current_time = current_time + HALF_DAY;
			}
			{
				// read files



			}


			// Part 2
			{
				// Send records from registries to heaps
				// Send Reg1:
				ListNode* node = &Reg1;
				while (!node->getForward()->isDummy())
				{
					node = node->getForward();
					FibNode new_fibnode;
					new_fibnode.setRecordData(
						node->getRecordID(), node->getRecordName(), node->getRecordAddress(), node->getRecordPhone(), node->getRecordWeChat(),
						node->getRecordEmail(), node->getRecordBirth(), node->getRecordProfession(), node->getRecordRisk(), node->getRecordRegistry()
					);
					if (2 == node->getRecordRisk()) {
						// 中风险代码
						new_fibnode.status = 2;
						medium_risk_heap->Insert(&new_fibnode);
					}
					else if (3 == node->getRecordRisk()) {
						// 高风险代码
						new_fibnode.status = 3;
						high_risk_heap->Insert(&new_fibnode);
					}
					else {
						// 无风险或低风险代码
						new_fibnode.status = 0;
						main_heap->Insert(&new_fibnode);

						FibNode new_fibnode2;
						new_fibnode2.setRecordData(
							node->getRecordID(), node->getRecordName(), node->getRecordAddress(), node->getRecordPhone(), node->getRecordWeChat(),
							node->getRecordEmail(), node->getRecordBirth(), node->getRecordProfession(), node->getRecordRisk(), node->getRecordRegistry()
						);
						new_fibnode2.status = 1;
						ddl_heap->Insert(&new_fibnode2);

					}
				}
			}
			{
				// 把中风险和撤回的时间到达的插入到main
				{
					// Insert withdraw heap node to main
					FibNode* fibnode;
					fibnode = withdraw_heap->Pop_Min();
					while (NULL != fibnode && 0 >= fibnode->getRecordPriority())
					{
						// Copy 2 version of the node
						FibNode* fib_copy_main;
						fib_copy_main = fibnode->deepcopy();
						fib_copy_main->status = 0;
						FibNode* fib_copy_ddl;
						fib_copy_ddl = fib_copy_main->deepcopy();
						fib_copy_ddl->status = 1;
						// Insert the node to main heaps
						main_heap->Insert(fib_copy_main);
						ddl_heap->Insert(fib_copy_ddl);
						// Remove it from withdraw heap
						withdraw_heap->remove(fibnode);
						fibnode = withdraw_heap->Pop_Min();
					}
				}
				{
					// Insert medium risk heap node to main
					FibNode* fibnode;
					fibnode = medium_risk_heap->Pop_Min();
					while (NULL != fibnode && 0 >= fibnode->getRecordPriority())
					{
						// Copy 2 version of the node
						FibNode* fib_copy_main;
						fib_copy_main = fibnode->deepcopy();
						fib_copy_main->status = 0;
						FibNode* fib_copy_ddl;
						fib_copy_ddl = fib_copy_main->deepcopy();
						fib_copy_ddl->status = 1;
						// Insert the node to main heaps
						main_heap->Insert(fib_copy_main);
						ddl_heap->Insert(fib_copy_ddl);
						// Remove it from withdraw heap
						medium_risk_heap->remove(fibnode);
						fibnode = medium_risk_heap->Pop_Min();
					}
				}
			}
			{
				// Heap send data to hospitals
				// Get hospital total capacity
				int hos_cap;
				hos_cap = Hos1.getCapacity() + Hos2.getCapacity();
				// Pop people from the heaps
				FibNode* fibnode;
				fibnode = ddl_heap->Pop_Min();
				while (fibnode->getRecordDeadline() > current_time) {

				}
				int id = fibnode->getRecordID();
				main_heap->remove(main_heap->idsearch(id));
			}

			// Part 3
			if (0 == gmtime(&current_time)->tm_wday)
			{
				// 在这里执行周报输出操作
			}
			if (current_month != gmtime(&current_time)->tm_mon)
			{
				// update current month for calculate
				current_month = gmtime(&current_time)->tm_mon;
				// 在这里执行月报输出操作
			}
		}
		default:
			break;
		}
	}

}