#pragma once
// Multiple head file only include once

// Include libraries
#include <iostream>

// Include our head files
#include "time_functions.h"
#include "RegNode.h"
#include "HosNode.h"

using namespace std;

extern const int reg_num;
extern const int hos_num;

/*=================================*
 * Function: input_msg
 * Created by CYTIN
 *---------------------
 *   Show input hint message, and
 * return input option value.
 *==================================*/
int input_msg();

/*=================================*
 * Function: menu_msg
 * Created by CYTIN
 *-------------------------
 *   Show main menu message, and
 * return the input option value
 *==================================*/
int menu_msg(time_t& time);

/*=================================*
 * Function: registry_msg
 * Created by CYTIN
 *-------------------------
 *   Show registry menu message, and
 * return the input option value
 *==================================*/
int registry_msg();

/*=================================*
 * Function: hospital_msg
 * Created by CYTIN
 *-------------------------
 *   Show hospital menu message, and
 * return the input option value
 *==================================*/
int hospital_msg();

/*=================================*
 * Function: show_registries
 * Created by CYTIN
 *-------------------------
 *   Print the information of all
 * registries.
 *==================================*/
void show_registries(RegNode* dummy);

/*=================================*
 * Function: show_hospitals
 * Created by CYTIN
 *-------------------------
 *   Print the information of all
 * hospitals.
 *==================================*/
void show_hospitals(HosNode* dummy);

/*=================================*
 * Function: print_welcome
 * Created by CYTIN
 *-------------------------
 *   Print "WELCOME" start page
 *==================================*/
void print_welcome();

/*=================================*
 * Function: print_welcome
 * Created by CYTIN
 *-------------------------
 *   Print "GOODBYE" end page
 *==================================*/
void print_goodbye();

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
    cout << "[6] Print all the records that have been rescued." << endl;
    cout << "[7] Filter records" <<endl;
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
 *   Show registry menu message, and
 * return the input option value
 *==================================*/
int registry_msg()
{
    cout << "===================================================" << endl;
    cout << "           >>  Registry Setting Menu  <<           " << endl;
    cout << "---------------------------------------------------" << endl;
    //cout << "[1] Add a new registry" << endl;
    cout << "[1] Modify mininum registrant number each half-day" << endl;
    cout << "[2] Modify maxinum registrant number each half-day" << endl;
    //cout << "[3] Modify input file directory" << endl;
    cout << "[3] Show all registries information" << endl;
    cout << "[9] Back to the main menu" << endl;
    cout << "===================================================" << endl;
    return input_msg();
}

/*=================================*
 * Function: hospital_msg
 * Created by CYTIN
 *-------------------------
 *   Show hospital menu message, and
 * return the input option value
 *==================================*/
int hospital_msg()
{
    cout << "===============================================" << endl;
    cout << "         >>  Registry Setting Menu  <<         " << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "[1] Modify hospital half-daily capacity" << endl;
    cout << "[2] Show all hospital information" << endl;
    cout << "[9] Back to the main menu" << endl;
    cout << "===============================================" << endl;
    return input_msg();
}

/*=================================*
 * Function: filter_msg
 * Created by CYTIN
 *-------------------------
 *   Show filter menu message, and
 * return the input option value
 *==================================*/
int filter_msg(){
    cout << "===============================================" << endl;
    cout << "         >>  Registry Setting Menu  <<         " << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "[0] Find records with given id" << endl;
    cout << "[1] Find records with given age" << endl;
    cout << "[2] Find records with given age group" << endl;
    cout << "[3] Find records with given profession number" << endl;
    cout << "[4] Find records with given risk" << endl;
    cout << "[5] Find records with given registry" << endl;
    cout << "[6] Find records with given hospital" << endl;
    cout << "[7] Find records with given treatment" << endl;
    cout << "[8] Find records with given status" << endl;
    cout << "[9] Back to the last page" << endl;
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
 * Function: show_hospitals
 * Created by CYTIN
 *-------------------------
 *   Print the information of all
 * hospitals.
 *==================================*/
void show_hospitals(HosNode* dummy)
{
    cout << endl;
    cout << "==========================================" << endl;
    cout << "       >>  Hospital Information  <<       " << endl;
    cout << "------------------------------------------" << endl;
    cout << "    Index\tCapacity" << endl;
    HosNode* node = dummy;
    for (int i = 0; i < hos_num; i++) {
        node = (*node).getForward();
        cout << "·    " << i << "\t\t" << (*node).getCapacity() << endl;
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