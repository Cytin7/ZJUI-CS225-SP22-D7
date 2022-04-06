#include "head.h"
#include <fstream>


int PrintMainPage() {
	int key;
	cout << "Input the key number to choose the operation:" << endl;
	cout << "[0]\tClose the program" << endl;
	cout << "[1]\tSet register information" << endl;
	cout << "[]\tWithdraw Record using ID" << endl;
	cout << "[]\tModify Record information" << endl;
	cout << "[]\tRead file for the registry" << endl;
	cout << "Please input the key value here:" << endl << ">>>";
	cin >> key;
	cout << endl;
	return key;
}

int PrintRegistrySetupPage()
{
	int key;
	cout << "Input the key number to choose the operation of registry setup:" << endl;
	cout << "[0]\tReturn to the main page" << endl;
	cout << "[1]\tAdd one new registry" << endl;
	cout << "Please input the key value here:" << endl << ">>>";
	cin >> key;
	cout << endl;
	return key;
}


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



	while (true)
	{
		input_key = PrintMainPage();
		switch (input_key)
		{
		case 0:
			cout << "The program is closed" << endl;
			return 0;
			break;
		case 1:
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