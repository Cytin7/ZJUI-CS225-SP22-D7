#include "../head.h"

tm time_diff(time_t* time1, time_t* time2)
{
	time_t seconds = difftime(*time1, *time2);
	return *gmtime(&seconds);
}
