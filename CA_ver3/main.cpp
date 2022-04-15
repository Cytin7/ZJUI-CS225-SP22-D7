// Include all head files
#include "time/time.h"
#include "Time Functions/Time Functions.h"
#include "Record/Record.h"
#include "ListNode/ListNode.h"
#include "FibNode/FibNode.h"
#include "FibHeap/FibHeap.h"
#include "Application/Application.h"
#include "modify/modify.h"
#include "withdraw/withdraw.h"
#include "Print Functions/Print Functions.h"
#include "LOADFILE/LOADFILE.h"
#include "Report/Report.h"

int main() {
	const time_t HALF_DAY = 43200;

	time_t current_time = time(NULL);           // initialize the date to current time when program starts
	tm current_tm;
	gmtime_s(&current_tm, &current_time);

	// record the current date for comparation
	//int current_year;
	int month;
	//int current_day;

	// store the number input
	int input_key = -1;     // main page key input
	int input_key2 = -1;    // seb page key input

	//current_year = gmtime_s(&current_time)->tm_year;
	month = current_tm.tm_mon;
	//current_year = gmtime_s(&current_time)->tm_year;

	//PNode<ListNode> registry_list;
	//registry_list.set_dummy();

	// Input file directories for registries
	string filedir1 = "./Data/INPUT_00.csv";
	string filedir2 = "./Data/INPUT_01.csv";
	string filedir3 = "./Data/INPUT_02.csv";

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
				gmtime_s(&current_tm, &current_time);
			}
			{
				// decrease the day counter in medium_risk and withdraw heap
				medium_risk_heap->LoopMinus(medium_risk_heap->getMin());
				withdraw_heap->LoopMinus(withdraw_heap->getMin());
			}
			{
				// read files
				string str; // temp variable for storing input string

				for (int i = 0; i < Reg1.getCapacity(); i++) {
					if (myfile1.eof()) {
						cout << "File EOF: All input are already read." << endl;
					}
					//number������
					getline(myfile1, str);
					string* line = split(str);
					ListNode NEW;
					int ID = atoll(line[0].c_str());
					int profession = atoll(line[6].c_str());
					int risk = atoll(line[8].c_str());

					int month = atoll((get_birth(line[7])[0].c_str()));
					int day = atoll((get_birth(line[7])[1].c_str()));
					int year = atoll((get_birth(line[7])[2].c_str()));

					int birth = tm2time(month, day, year);

					NEW.setRecordID(ID);
					NEW.setRecordName(line[1]);
					NEW.setRecordAddress(line[2]);
					NEW.setRecordPhone(line[3]);
					NEW.setRecordWeChat(line[4]);
					NEW.setRecordEmail(line[5]);
					NEW.setRecordProfession(profession);
					NEW.setRecordBirth(birth,current_time);
					NEW.setRecordRisk(risk);

					Reg1.append(&NEW);
				}

				for (int i = 0; i < Reg2.getCapacity(); i++) {
					if (myfile2.eof()) {
						cout << "File EOF: All input are already read." << endl;
					}
					//number������
					getline(myfile2, str);
					string* line = split(str);
					ListNode NEW;
					int ID = atoll(line[0].c_str());
					int profession = atoll(line[6].c_str());
					int risk = atoll(line[8].c_str());

					int month = atoll((get_birth(line[7])[0].c_str()));
					int day = atoll((get_birth(line[7])[1].c_str()));
					int year = atoll((get_birth(line[7])[2].c_str()));

					int birth = tm2time(month, day, year);

					NEW.setRecordID(ID);
					NEW.setRecordName(line[1]);
					NEW.setRecordAddress(line[2]);
					NEW.setRecordPhone(line[3]);
					NEW.setRecordWeChat(line[4]);
					NEW.setRecordEmail(line[5]);
					NEW.setRecordProfession(profession);
					NEW.setRecordBirth(birth,current_time);
					NEW.setRecordRisk(risk);

					Reg2.append(&NEW);
				}

				for (int i = 0; i < Reg3.getCapacity(); i++) {
					if (myfile3.eof()) {
						cout << "File EOF: All input are already read." << endl;
					}
					//number������
					getline(myfile3, str);
					string* line = split(str);
					ListNode NEW;
					int ID = atoll(line[0].c_str());
					int profession = atoll(line[6].c_str());
					int risk = atoll(line[8].c_str());

					int month = atoll((get_birth(line[7])[0].c_str()));
					int day = atoll((get_birth(line[7])[1].c_str()));
					int year = atoll((get_birth(line[7])[2].c_str()));

					int birth = tm2time(month, day, year);

					NEW.setRecordID(ID);
					NEW.setRecordName(line[1]);
					NEW.setRecordAddress(line[2]);
					NEW.setRecordPhone(line[3]);
					NEW.setRecordWeChat(line[4]);
					NEW.setRecordEmail(line[5]);
					NEW.setRecordProfession(profession);
					NEW.setRecordBirth(birth,current_time);
					NEW.setRecordRisk(risk);

					Reg3.append(&NEW);
				}

			}


			// Part 2
			{
				// Send records from registries to heaps
				// Send Reg1:
				ListNode* node = Reg1.getForward();
				while (!node->isDummy())
				{

					FibNode new_fibnode;
					new_fibnode.setRecordData(
						node->getRecordID(), node->getRecordName(), node->getRecordAddress(), node->getRecordPhone(), node->getRecordWeChat(),
						node->getRecordEmail(), node->getRecordBirth(), node->getRecordProfession(), node->getRecordRisk(), node->getRecordRegistry(), current_time
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
							node->getRecordEmail(), node->getRecordBirth(), node->getRecordProfession(), node->getRecordRisk(), node->getRecordRegistry(),current_time
						);
						new_fibnode2.status = 1;
						ddl_heap->Insert(&new_fibnode2);

					}
					node = node->getForward();
				}
			}
			{
				// ���з��պͳ��ص�ʱ�䵽��Ĳ��뵽main
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
				int counter = 0;
				while (fibnode != NULL && fibnode->get_priority_number() <= current_tm.tm_mon * 100 + current_tm.tm_mday && counter < hos_cap) {
					counter += 1;
					ListNode new_hos_record;
					new_hos_record.setRecordData(fibnode->getRecordID(), fibnode->getRecordName(), fibnode->getRecordAddress(), fibnode->getRecordPhone(), fibnode->getRecordWeChat(), fibnode->getRecordEmail(), fibnode->getRecordBirth(), fibnode->getRecordProfession(), fibnode->getRecordRisk(), fibnode->getRecordRegistry(), current_time);
					if (counter < Hos1.getCapacity()) {
						new_hos_record.setRecordHospital(1);
						Hos1.append(&new_hos_record);
					}
					else {
						new_hos_record.setRecordHospital(2);
						Hos2.append(&new_hos_record);
					}
					main_heap->remove(main_heap->idsearch(main_heap->getMin(), fibnode->getRecordID()));
					ddl_heap->remove(fibnode);
					fibnode = ddl_heap->getMin();
				}
				if (counter < hos_cap) {
					while (counter < hos_cap && main_heap->getMin() != NULL) {
						counter += 1;
						ListNode new_hos_record;
						new_hos_record.setRecordData(fibnode->getRecordID(), fibnode->getRecordName(), fibnode->getRecordAddress(), fibnode->getRecordPhone(), fibnode->getRecordWeChat(), fibnode->getRecordEmail(), fibnode->getRecordBirth(), fibnode->getRecordProfession(), fibnode->getRecordRisk(), fibnode->getRecordRegistry(), current_time);
						if (counter < Hos1.getCapacity()) {
							new_hos_record.setRecordHospital(1);
							Hos1.append(&new_hos_record);
						}
						else {
							new_hos_record.setRecordHospital(2);
							Hos2.append(&new_hos_record);
						}
						ddl_heap->remove(ddl_heap->idsearch(ddl_heap->getMin(), fibnode->getRecordID()));
						main_heap->remove(fibnode);
						fibnode = main_heap->getMin();
					}
				}
				if (counter < hos_cap) {
					while (counter < hos_cap && high_risk_heap->getMin() != NULL) {
						counter += 1;
						ListNode new_hos_record;
						new_hos_record.setRecordData(fibnode->getRecordID(), fibnode->getRecordName(), fibnode->getRecordAddress(), fibnode->getRecordPhone(), fibnode->getRecordWeChat(), fibnode->getRecordEmail(), fibnode->getRecordBirth(), fibnode->getRecordProfession(), fibnode->getRecordRisk(), fibnode->getRecordRegistry(), current_time);
						if (counter < Hos1.getCapacity()) {
							new_hos_record.setRecordHospital(1);
							Hos1.append(&new_hos_record);
						}
						else {
							new_hos_record.setRecordHospital(2);
							Hos2.append(&new_hos_record);
						}
						high_risk_heap->remove(fibnode);
						fibnode = high_risk_heap->getMin();
					}
				}


			}

			// Part 3
			tm current_tm;
			gmtime_s(&current_tm, &current_time);
			if (0 == current_tm.tm_wday)
			{
				// ������ִ���ܱ��������

			}
			if (month != current_tm.tm_mon)
			{
				// update current month for calculate
				month = current_tm.tm_mon;
				// ������ִ���±��������
			}

		}
		default:
			break;
		}
	}

}