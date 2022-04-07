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

	FibHeap* ddl_heap = new FibHeap;
	FibHeap* main_heap = new FibHeap;
	FibHeap* high_risk_heap = new FibHeap;
	FibHeap* medium_risk_heap = new FibHeap;
	FibHeap* withdraw_heap = new FibHeap;

	Reg1.setDummy();
	Reg2.setDummy();
	Reg3.setDummy();

	Reg1.setCapacity(5);
	Reg2.setCapacity(5);
	Reg3.setCapacity(5);

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
						// �з��մ���
						new_fibnode.status = 2;
						medium_risk_heap->Insert(&new_fibnode);
					}
					else if (3 == node->getRecordRisk()) {
						// �߷��մ���
						new_fibnode.status = 3;
						high_risk_heap->Insert(&new_fibnode);
					}
					else {
						// �޷��ջ�ͷ��մ���
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
				// ���з��պͳ��ص�ʱ�䵽��Ĳ��뵽main
				FibNode* fibnode;
				fibnode = withdraw_heap->Pop_Min();
				while (0 >= fibnode->getRecordPriority())
				{

				}
			}
			{
				// Heap send data to hospitals

				FibNode* fibnode;
				fibnode = main_heap->Pop_Min();
				while (0 >= fibnode->getRecordPriority()) {

				}
				int id = fibnode->getRecordID();
				main_heap->remove(main_heap->idsearch(id));
			}

			// Part 3
			if (0 == gmtime(&current_time)->tm_wday)
			{
				// ������ִ���ܱ��������
			}
			if (current_month != gmtime(&current_time)->tm_mon)
			{
				// update current month for calculate
				current_month = gmtime(&current_time)->tm_mon;
				// ������ִ���±��������
			}
		}
		default:
			break;
		}
	}

}