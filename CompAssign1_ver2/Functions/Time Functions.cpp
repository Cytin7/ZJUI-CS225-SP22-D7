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

string DatetimeToString(time_t time)
{
    tm *tm_ = localtime(&time);                // 将time_t格式转换为tm结构体
    int year, month, day;// 定义时间的各个int临时变量。
    year = tm_->tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
    month = tm_->tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
    day = tm_->tm_mday;                        // 临时变量，日。
    char yearStr[5], monthStr[3], dayStr[3];// 定义时间的各个char*变量。
    sprintf(yearStr, "%d", year);              // 年。
    sprintf(monthStr, "%d", month);            // 月。
    sprintf(dayStr, "%d", day);                // 日。


    char s[20];                                // 定义总日期时间char*变量。
    sprintf(s, "%s/%s/%s",monthStr, dayStr,yearStr);// 将月日年合并。
    string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
    return str;                                // 返回转换日期时间后的string变量。
}
