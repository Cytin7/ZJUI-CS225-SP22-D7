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

using namespace std;

// Set number of registries
#define registry_number 7



// global variables
const int reg_num = registry_number;

// Main Program
int main() {
	// Space for declaring necessary variables and objects
	// program time step
	const time_t HALF_DAY = 43200;
	// current time for system simulation
	time_t current_time = time(NULL);
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
	// center database stuctures
	ListNode* medium_risk_list = new ListNode;
	ListNode* withdraw_list = new ListNode;
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
		case 1:
		{
			// Time step forward for half day
			current_time += HALF_DAY;
			// Read files
			char tmp[256] = {};
			string data;
			RegNode* reg = registries.getForward();
			// Read file data for registrants record data
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
			break;
		}
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
		case 9:
		{
			// Quit the program
			cout << "Closing the program..." << endl << endl;
			print_goodbye();
			return 0;
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