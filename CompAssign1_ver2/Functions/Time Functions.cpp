#include "../head.h"

tm time_diff(time_t* time1, time_t* time2)
{
	time_t seconds = difftime(*time1, *time2);
	return *gmtime(&seconds);
}

time_t tm2time( int month, int day, int year, int hour = 0, int minute = 0, int second = 0)
{
	tm date;
	date.tm_year = year;
	date.tm_mon = month;
	date.tm_mday = day;
	date.tm_hour = hour;
	date.tm_min = minute;
	date.tm_sec = second;
	return mktime(&date);
}