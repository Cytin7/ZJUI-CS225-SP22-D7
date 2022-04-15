#include "IO_functions.h"

/*=================================*
 * Function: input_msg
 * Created by CYTIN
 *---------------------
 *   Show input hint message, and
 * return input option value.
 *==================================*/
int input_msg()
{
	cin.clear();   // clear the error of wrong data type
	int input_key = 0;
	cout << "Please input the value here:" << endl;
	cout << ">>>";
	while (!(cin >> input_key)) {
		cin.clear();   // clear the error of wrong data type
		cin.ignore();  // clear the content of wrong data
		cout << "Please input a valid value here:" << endl;
		cout << ">>>";

	}
	return input_key;
}

/*=================================*
 * Function: menu_msg
 * Created by CYTIN
 *-------------------------
 *   Show main menu message, and
 * return the input option value
 *==================================*/
int menu_msg(time_t& time)
{
	cout << endl;
	cout << "==========================================" << endl;
	cout << "            >>  Main  menu  <<            " << endl;
	cout << "------------------------------------------" << endl;
	cout << "[1] Time step forward for half day" << endl;
	cout << "[2] Set up registry information" << endl;
	cout << "[3] Set up hospital information" << endl;
	cout << "[4] Withdraw a record with id" << endl;
	cout << "[5] Modify a record information with id" << endl;
	cout << "[9] Quit the program" << endl;
	cout << "------------------------------------------" << endl;
	cout << "   " << date_str(time) << "\t\t\t" << time_str(time) << endl;
	cout << "==========================================" << endl;
	return input_msg();
}

/*=================================*
 * Function: registry_msg
 * Created by CYTIN
 *-------------------------
 *   Show main menu message, and
 * return the input option value
 *==================================*/
int registry_msg()
{
	cout << "===============================================" << endl;
	cout << "         >>  Registry Setting Menu  <<         " << endl;
	cout << "-----------------------------------------------" << endl;
	//cout << "[1] Add a new registry" << endl;
	cout << "[1] Modify mininum registrant number each day" << endl;
	cout << "[2] Modify maxinum registrant number each day" << endl;
	//cout << "[3] Modify input file directory" << endl;
	cout << "[3] Show all registries information" << endl;
	cout << "[9] Back to the main menu" << endl;
	cout << "===============================================" << endl;
	return input_msg();
}

/*=================================*
 * Function: show_registries
 * Created by CYTIN
 *-------------------------
 *   Print the information of all
 * registries.
 *==================================*/
void show_registries(RegNode* dummy)
{
	cout << endl;
	cout << "==========================================" << endl;
	cout << "       >>  Registry Information  <<       " << endl;
	cout << "------------------------------------------" << endl;
	cout << "    Index\tMin Input\tMax Input" << endl;
	RegNode* node = dummy;
	for (int i = 0; i < reg_num; i++) {
		node = (*node).getForward();
		cout << "·    " << i << "\t\t" << (*node).getMin() << "\t\t" << (*node).getMax() << endl;
	}
	cout << "==========================================" << endl;
	return;
}

/*=================================*
 * Function: print_welcome
 * Created by CYTIN
 *-------------------------
 *   Print "WELCOME" start page
 *==================================*/
void print_welcome()
{
	cout << "██╗    ██╗ ███████╗ ██╗       ██████╗  ██████╗  ███╗   ███╗ ███████╗" << endl;
	cout << "██║    ██║ ██╔════╝ ██║      ██╔════╝ ██╔═══██╗ ████╗ ████║ ██╔════╝" << endl;
	cout << "██║ █╗ ██║ █████╗   ██║      ██║      ██║   ██║ ██╔████╔██║ █████╗  " << endl;
	cout << "██║███╗██║ ██╔══╝   ██║      ██║      ██║   ██║ ██║╚██╔╝██║ ██╔══╝  " << endl;
	cout << "╚███╔███╔╝ ███████╗ ███████╗ ╚██████╗ ╚██████╔╝ ██║ ╚═╝ ██║ ███████╗" << endl;
	cout << " ╚══╝╚══╝  ╚══════╝ ╚══════╝  ╚═════╝  ╚═════╝  ╚═╝     ╚═╝ ╚══════╝" << endl;
}

/*=================================*
 * Function: print_welcome
 * Created by CYTIN
 *-------------------------
 *   Print "GOODBYE" end page
 *==================================*/
void print_goodbye()
{
	cout << " ██████╗   ██████╗   ██████╗  ██████╗  ██████╗  ██╗   ██╗ ███████╗" << endl;
	cout << "██╔════╝  ██╔═══██╗ ██╔═══██╗ ██╔══██╗ ██╔══██╗ ╚██╗ ██╔╝ ██╔════╝" << endl;
	cout << "██║  ███╗ ██║   ██║ ██║   ██║ ██║  ██║ ██████╔╝  ╚████╔╝  █████╗  " << endl;
	cout << "██║   ██║ ██║   ██║ ██║   ██║ ██║  ██║ ██╔══██╗   ╚██╔╝   ██╔══╝  " << endl;
	cout << "╚██████╔╝ ╚██████╔╝ ╚██████╔╝ ██████╔╝ ██████╔╝    ██║    ███████╗" << endl;
	cout << " ╚═════╝   ╚═════╝   ╚═════╝  ╚═════╝  ╚═════╝     ╚═╝    ╚══════╝" << endl;
}


