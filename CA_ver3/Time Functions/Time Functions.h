#pragma once
// Multiple head file only include once

// Include libraries
#include <ctime>

/*=============================================*
 * Function time_diff
 * ------------------
 *     Calculate year,month,day between two
 * time stamps
 *=============================================*/
tm time_diff(time_t* time1, time_t* time2);

/*=============================================*
 * Function tm2time
 * ----------------
 *     transfrom date to time_t
 *=============================================*/
time_t tm2time(int month, int day, int year);