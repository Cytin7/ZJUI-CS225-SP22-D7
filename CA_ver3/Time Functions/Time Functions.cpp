#include "Time Functions.h"

tm time_diff(time_t* time1, time_t* time2)
{
	time_t seconds = difftime(*time1, *time2);
	tm tmp;
	gmtime_s(&tmp, &seconds);
	return tmp;
}

time_t tm2time(int month, int day, int year)
{
	tm date{};
	date.tm_year = year;
	date.tm_mon = month;
	date.tm_mday = day;
	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 0;
	return mktime(&date);
}
