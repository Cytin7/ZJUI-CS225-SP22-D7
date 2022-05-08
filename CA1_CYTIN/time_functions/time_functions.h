#pragma once
// Multiple head file only include once

// Include libraries
#include <string>
#include <ctime>

using namespace std;

/*=================================*
 * Function: date_str
 * Created by CYTIN
 *---------------------
 *   transfer time_t to date string
 *==================================*/
string date_str(time_t& time);

/*=================================*
 * Function: time_str
 * Created by CYTIN
 *---------------------
 *   transfer time_t to time string
 *==================================*/
string time_str(time_t& time);

/*=================================*
 * Function: time_diff
 * Created by CYTIN
 *---------------------
 *   Calculate duration between two
 * time and return in struct tm
 *==================================*/
tm time_diff(time_t& end, time_t& start);

/*=================================*
 * Function: str2date
 * Created by CYTIN
 *---------------------
 *   Transfer M/D/Y date string to
 * time_t time stamp
 *==================================*/
time_t str2date(string str);