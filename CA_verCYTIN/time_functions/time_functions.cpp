#include "time_functions.h"
#include <iostream>

/*=================================*
 * Function: date_str
 * Created by CYTIN
 *---------------------
 * transfer time_t to date string
 *==================================*/
string date_str(time_t& time) {
	if (0 == time) {
		return "";
	}
	tm tmp;
	localtime_s(&tmp, &time);
	string mon_name[12] = { "Jan.","Feb.","Mar.","Apr.","May.","Jun.","Jul.","Aug.","Sept.","Oct.","Nov.","Dec." };
	return (mon_name[tmp.tm_mon] + to_string(tmp.tm_mday) + ", " + to_string(1900 + tmp.tm_year));
}

/*=================================*
 * Function: time_str
 * Created by CYTIN
 *---------------------
 * transfer time_t to time string
 *==================================*/
string time_str(time_t& time)
{
	tm tmp;
	localtime_s(&tmp, &time);
	string minute = to_string(tmp.tm_min);
	if (10 > tmp.tm_min) {
		minute = "0" + minute;
	}
	return (to_string(tmp.tm_hour) + ":" + minute);
}

/*=================================*
 * Function: time_diff
 * Created by CYTIN
 *---------------------
 *   Calculate duration between two
 * time and return in struct tm
 *==================================*/
tm time_diff(time_t& end, time_t& start)
{
	time_t seconds = difftime(end, start);
	tm tmp;
	gmtime_s(&tmp, &seconds);
	return tmp;
}

/*=================================*
 * Function: str2date
 * Created by CYTIN
 *---------------------
 *   Transfer M/D/Y date string to
 * time_t time stamp
 *==================================*/
time_t str2date(string str)
{
	// Split date string
	string data[3] = {};
	{
		int len = str.length();
		int index = 0;
		string tmp = "";
		for (int i = 0; i < len; i++) {
			if ('/' == str[i]) {
				data[index] = tmp;
				tmp = "";
				index++;
			}
			else {
				tmp = tmp + str[i];
			}
		}
		data[index] = tmp;
	}
	// Generate time stamp
	tm tm_tmp = {};
	tm_tmp.tm_mon = stoi(data[0]) - 1;
	tm_tmp.tm_mday = stoi(data[1]);
	tm_tmp.tm_year = stoi(data[2]) - 1900;
	return mktime(&tm_tmp);
}
