#pragma once
// Multiple head file only include once

// Include libraries

// Include our head files
#include "../Class_Record/Record.h"
#include "../time_functions/time_functions.h"

/*=================================*
 * Function: dataLine2Record
 * Created by CYTIN
 *----------------------------
 *   Generate record using data
 * from input string.
 *==================================*/
Record* dataLine2Record(string str, time_t current_time);

/*=================================*
 * Function: correctDir
 * Created by CYTIN
 *----------------------------
 * Modify inout dir to C++ string
 *==================================*/
string correctDir(string inputDir);

/*=================================*
 * Function: strjust
 * Created by CYTIN
 *----------------------------
 * Modify inout dir to C++ string
 *==================================*/
string strjust(string str, int len, char c = ' ');