#include "str_funcions.h"

/*=================================*
 * Function: dataLine2Record
 * Created by CYTIN
 *----------------------------
 *   Generate record using data
 * from input string.
 *==================================*/
Record* dataLine2Record(string str, time_t current_time)
{
	string data[11] = {};
	{
		// split csv data
		int i = 0;
		int counter = 0;
		string tmp = "";
		int len = str.length();
		while (i < len) {
			if ('"' == str[i]) {
				// process data with quotation mark
				tmp = "";
				i++;
				while ('"' != str[i]) {
					tmp = tmp + str[i];
					i++;
				}
			}
			else if (',' == str[i]) {
				// split data when meeting comma or string end
				data[counter] = tmp;
				tmp = "";
				counter++;
			}
			else if ('\n' == str[i]) {
				// in case the string ends with \n
			}
			else {
				tmp = tmp + str[i];
			}
			i++;
		}
		// the last data has no comma
		data[counter] = tmp;
	}
	// construct Record
	Record* record = new Record;
	(*record).setRecordID(stoi(data[0]));
	(*record).setRecordName(data[1]);
	(*record).setRecordAddress(data[2]);
	(*record).setRecordPhone(data[3]);
	(*record).setRecordWeChat(data[4]);
	(*record).setRecordEmail(data[5]);
	(*record).setRecordBirth(str2date(data[7]), current_time);
	(*record).setRecordProfession(stoi(data[6]));
	(*record).setRecordRisk(stoi(data[8]));
	if ("True" != data[9]) {
		(*record).setRecordDeadline(str2date(data[10]));
	}
	(*record).setRecordRegisterTime(current_time);
	return record;
}

/*=================================*
 * Function: correctDir
 * Created by CYTIN
 *----------------------------
 * Modify inout dir to C++ string
 *==================================*/
string correctDir(string inputDir)
{
	string dir = "";
	int len = inputDir.length();
	for (int i = 0; i < len; i++) {
		if ('"' == inputDir[i]) {
			continue;
		}
		else if (inputDir[i] == '\\' || inputDir[i] == '/')
		{
			dir = dir + "/";
		}
		else {
			dir = dir + inputDir[i];
		}
	}
	return dir;
}

/*=================================*
 * Function: strjust
 * Created by CYTIN
 *----------------------------
 * Modify inout dir to C++ string
 *==================================*/
string strjust(string str, int len, char c)
{
	int slen = str.length();
	if (slen < len) {
		while (++slen <= len) {
			str = str + c;
		}
		return str;
	}
	else
	{
		return str;
	}
}