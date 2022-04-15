#pragma once
// Multiple head file only include once

// Include libraries
#include <iostream>

// Include our head files
#include "../time_functions/time_functions.h"
#include "../Class_RegNode/RegNode.h"

using namespace std;

extern const int reg_num;

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
 *   Show main menu message, and
 * return the input option value
 *==================================*/
int registry_msg();

/*=================================*
 * Function: show_registries
 * Created by CYTIN
 *-------------------------
 *   Print the information of all
 * registries.
 *==================================*/
void show_registries(RegNode* dummy);

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