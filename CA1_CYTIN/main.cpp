// Include required libraries
#include <fstream>
// Include all head files
#include "time_functions/time_functions.h"
#include "IO_functions/IO_functions.h"
#include "Class_Record/Record.h"
#include "str_funcions/str_funcions.h"
#include "node_functions/node_functions.h"
#include "Class_ListNode/ListNode.h"
#include "Class_RegNode/RegNode.h"
#include "Class_FibNode/FibNode.h"
#include "Class_FibHeap/FibHeap.h"
#include "Class_HosNode/HosNode.h"

using namespace std;

// Set number of registries
#define registry_number 7
#define hospital_number 5
#define HALF_DAY 43200



// global variables
const int reg_num = registry_number;
const int hos_num = hospital_number;

// Main Program
int main() {
	// Space for declaring necessary variables and objects
	//// program time step
	//const time_t HALF_DAY = 43200;
	// current time for system simulation
	time_t current_time = time(nullptr);

	// Set rand() seed
	srand((unsigned)current_time);

	// Create file input streams
	fstream reg_file[registry_number] = {};
	// Create structure objects
	RegNode registries;
	registries.setDummy();
	char tmp[256];
	for (int i = 0; i < registry_number; i++) {
		reg_file[i].open("./Data/Data" + to_string(i + 1) + ".csv", ios::in);
		reg_file[i].getline(tmp, 256, '\n');  //Remove csv title
		RegNode* new_node = new RegNode;
		(*new_node).setData(i);// &reg_file[i]);
		registries.append(new_node);
	}
	HosNode hospitals;
	hospitals.setDummy();
	for (int i = 0; i < hospital_number; i++) {
		HosNode* new_node = new HosNode;
		(*new_node).setData(i);
		hospitals.append(new_node);
	}

	// center database stuctures
	ListNode* medium_risk_list = new ListNode;
	(*medium_risk_list).setDummy();
	ListNode* withdraw_list = new ListNode;
	(*withdraw_list).setDummy();
	FibHeap* main_heap = new FibHeap;
	FibHeap* ddl_heap = new FibHeap;
	FibHeap* high_risk_heap = new FibHeap;

	// For menu key value
	int menu_key = 0;
	int submenu_key = 0;

	// Start program
	print_welcome();
	// Major loop for operation and time step in
	while (true)
	{
		// print the main menu and get operation key
		menu_key = menu_msg(current_time);
		switch (menu_key)
		{
			// Modify Regisries
		case 2:
		{
			cin.clear();   // clear the error of wrong data type
			cin.ignore();  // clear the content of wrong data
			submenu_key = registry_msg();
			switch (submenu_key)
			{
			case 1:
			{
				show_registries(&registries);
				cout << "Input the index of registry to modify mininum registrants per day." << endl;
				int index = input_msg();
				if (index < 0 || index >= registry_number) {
					cout << "Registry does not exist." << endl;
					break;
				}
				RegNode* node = &registries;
				for (int i = 0; i <= index; i++) {
					node = (*node).getForward();
				}
				cout << "Input the new mininum registrants per day:" << endl;
				int min = input_msg();
				if (min < 0) {
					cout << "Registant number cannot be negative." << endl;
					break;
				}
				else if (min > (*node).getMax()) {
					(*node).setMin((*node).getMax());
					(*node).setMax(min);
				}
				else {
					(*node).setMin(min);
				}
				break;
			}
			case 2:
			{
				show_registries(&registries);
				cout << "Input the index of registry to modify maxinum registrants per day." << endl;
				int index = input_msg();
				if (index < 0 || index >= registry_number) {
					cout << "Registry does not exist." << endl;
					break;
				}
				RegNode* node = &registries;
				for (int i = 0; i <= index; i++) {
					node = (*node).getForward();
				}
				cout << "Input the new maxinum registrants per day:" << endl;
				int max = input_msg();
				if (max < 0) {
					cout << "Registant number cannot be negative." << endl;
					break;
				}
				else if (max < (*node).getMin()) {
					(*node).setMax((*node).getMin());
					(*node).setMin(max);
				}
				else {
					(*node).setMax(max);
				}
				break;
			}
			case 3:
			{
				show_registries(&registries);
				break;
			}
			case 9:
				break;
			default:
				cout << "Error: Operation code not found. Please Try again" << endl;
				break;
			}
			break;
		}
		// Modify Hospitals
		case 3:
		{
			cin.clear();   // clear the error of wrong data type
			cin.ignore();  // clear the content of wrong data
			submenu_key = hospital_msg();
			switch (submenu_key)
			{
			case 1:
				show_hospitals(&hospitals);
				break;
			case 2:
				show_hospitals(&hospitals);
				break;
			case 9:
				break;
			default:
				cout << "Error: Operation code not found. Please Try again" << endl;
				break;
			}
			break;
		}
		// Exit the program
		case 9:
		{
			// Quit the program
			cout << "Closing the program..." << endl << endl;
			for (int i = 0; i < registry_number; i++) {
				reg_file[i].close();
			}
			delete[] reg_file;
			print_goodbye();
			return 0;
		}
		// Main loop -> half day simulation
		case 1:
		{
			// Time step forward for half day
			current_time += HALF_DAY;
			// Read files
			char tmp[256] = {};
			string data;
			RegNode* reg = registries.getForward();
			// Read file data for registrants record data
			// For real simulation, every halfday, the regitory take in random number people, within a set range
			// and the filestream always hold in the main program, read line by line each halfday
			// all value are stored in the link node
			for (int i = 0; i < registry_number; i++) {
				int read_num = rand() % ((*reg).getMax() - (*reg).getMin() + 1) + (*reg).getMin();
				if (reg_file[i].eof()) {
					continue;
				}
				for (int j = 0; j < read_num; j++) {
					reg_file[i].getline(tmp, 256, '\n');
					data = tmp;
					if (reg_file[i].eof() || data == "") {
						break;
					}
					else {
						ListNode* node = new ListNode;
						(*node).setRecordwithData(data, i, current_time);
						(*reg).getList()->append(node);
					}
				}
				(*reg).printAllRecords();
				reg = (*reg).getForward();
			}
			cout << "主堆num" << main_heap->getNumitems() << endl;
			// send data to main heap
			{
				reg = registries.getForward();
				ListNode* ptr;
				for (int i = 0; i < registry_number; i++) {

					ptr = (*(*(*reg).getList()).getOld()).getForward();

					while (!(*ptr).getDummyBool()) {

						FibNode* fibn, * fibc;
						ListNode* listn;
						switch ((*(*ptr).getRecord()).getRecordRisk())
						{
						case 0:
						case 1:
							fibn = (*ptr).toFibNode();
							(*main_heap).insert(fibn, major_prior);
							if ((*(*ptr).getRecord()).getRecordDDLBool()) {
								fibc = (*fibn).copy();
								(*ddl_heap).insert(fibc, ddl_prior);
							}
							break;
						case 2:
							// medium risk
							listn = (*ptr).copy();
							(*medium_risk_list).insert(listn);
							break;
						case 3:
							// high risk
							fibn = (*ptr).toFibNode();
							(*high_risk_heap).insert(fibn, major_prior);
							break;
						default:
							break;
						}
						ptr = (*ptr).getForward();
					}
					// set old to new value;
					(*(*reg).getList()).setOld(((*reg).getList()->getBackward()));
					reg = (*reg).getForward();
				}
			}
			// transport eligible record in withdraw list to main heap
			while (!(*(*withdraw_list).getBackward()).getDummyBool())
			{
				FibNode* fibn, * fibc;
				ListNode* listn = (*withdraw_list).getBackward();
				Record* record = (*listn).getRecord();
				if (current_time >= ((*record).getRecordRegisterTime() + 14 * 2 * HALF_DAY)) {
					listn = (*withdraw_list).drop();
					(*record).setRecordRegisterTime(current_time);
					switch ((*record).getRecordRisk())
					{
					case 0:
					case 1:
						fibn = (*listn).toFibNode();
						(*main_heap).insert(fibn, major_prior);
						if ((*record).getRecordDDLBool()) {
							fibc = (*fibn).copy();
							(*ddl_heap).insert(fibc, ddl_prior);
						}
						delete listn;
						break;
					case 2:
						(*medium_risk_list).insert(listn);
						break;
					case 3:
						fibn = (*listn).toFibNode();
						(*high_risk_heap).insert(fibn, major_prior);
						delete listn;
						break;
					default:
						break;
					}
				}
				else {
					break;
				}
			}
			// transport eligible record in medium risk list to main heap
			while (!(*(*medium_risk_list).getBackward()).getDummyBool())
			{
				FibNode* fibn, * fibc;
				ListNode* listn = (*medium_risk_list).getBackward();
				Record* record = (*listn).getRecord();
				time_t time = (*record).getRecordRegisterTime();
				if (current_time >= ((*record).getRecordRegisterTime() + 5 * 2 * HALF_DAY)) {
					listn = (*medium_risk_list).drop();
					fibn = (*listn).toFibNode();
					(*main_heap).insert(fibn, major_prior);
					if ((*record).getRecordDDLBool()) {
						fibc = (*fibn).copy();
						(*ddl_heap).insert(fibc, ddl_prior);

					}
					delete listn;
				}
				else {
					break;
				}
			}

			cout << "主堆num" << main_heap->getNumitems() << endl;
			cout << "开始导出数据" << endl;
			// assign patient to hospitals
			{
				HosNode* hos = hospitals.getForward();
				ListNode* listn;
				int cap, counter;
				for (int i = 0; i < hospital_number; i++)
				{
					cap = (*hos).getCapacity();
					cout << "第" << i + 1 << "个医院，容量为" << cap << endl;
					counter = 0;
					while ((counter < cap) && (0 != (*ddl_heap).getNumitems())) {
						if ((current_time + 2 * HALF_DAY) <= (*(*(*ddl_heap).getMin()).getRecord()).getRecordDeadline()) {
							listn = toListNode((*ddl_heap).pop_min(ddl_prior));
							(*(*hos).getList()).append(listn);

							int id = (*(*listn).getRecord()).getRecordID();
							cout << "检测用输出\t" << id << endl;
							(*main_heap).delete_node(id, major_prior);
							counter++;
						}
						else {
							break;
						}
					}
					cout << "在这里谁便加入一句话检测是否运行了" << endl;
					while ((counter < cap) && (0 != (*main_heap).getNumitems())) {
						listn = toListNode(&(*(*main_heap).pop_min(major_prior)));
						(*(*hos).getList()).append(listn);
						if ((*(*listn).getRecord()).getRecordDDLBool()) {
							(*ddl_heap).delete_node((*(*listn).getRecord()).getRecordID(), ddl_prior);
						}
						counter++;
					}
					while ((counter < cap) && (0 != (*high_risk_heap).getNumitems())) {
						listn = toListNode(&(*(*high_risk_heap).pop_min(major_prior)));
						(*(*hos).getList()).append(listn);
						counter++;
					}
					if (counter < cap) {
						cout << "堆已经空" << endl;
						cout << "主堆num" << main_heap->getNumitems() << endl;
					}
					hos = (*hos).getForward();
				}
			}

			// week report
			// 

			// month report 
			break;
		}
		default:
			cout << "Error: Operation code not found. Please Try again" << endl;
			break;
		}
		menu_key = 0;
		submenu_key = 0;
		cin.clear();   // clear the error of wrong data type
		cin.ignore();  // clear the content of wrong data
	}
}