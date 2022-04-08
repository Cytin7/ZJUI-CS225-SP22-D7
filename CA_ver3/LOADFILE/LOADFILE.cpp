#include "LOADFILE.h"



string ReadLine(char* filename, int line)
{
	int lines, i = 0;
	string temp;
	fstream file;
	file.open(filename, ios::in);
	lines = CountLines(filename);

	if (line <= 0)
	{
		return "Error 1: line index error, the index cannot be 0 or negative";
	}
	if (file.fail())
	{
		return "Error 2: The file does not exist";
	}
	if (line > lines)
	{
		return "Error 3: line index overflow";
	}
	while (getline(file, temp) && i < line - 1)
	{
		i++;
	}
	file.close();
	return temp;
}

int CountLines(char* filename)
{
	ifstream ReadFile;
	int n = 0;
	string tmp;
	ReadFile.open(filename, ios::in);//ios::in 表示以只读的方式读取文件
	if (ReadFile.fail())//文件打开失败:返回0
	{
		return 0;
	}
	else//文件存在
	{
		while (getline(ReadFile, tmp, '\n'))
		{
			n++;
		}
		ReadFile.close();
		return n;
	}
}
//Helper function split
string* split(string i)
{
	string* ret = new string[20];
	int counter = 0;
	for (int j = 0; j < 14; j++)
	{
		string temp = "";
		while (i[counter] != '\0')
		{
			if( (i[counter] == ',')&& (i[counter + 1] == ' '))
			{
				counter++;
				break;
			}
			temp += i[counter];
			counter++;
		}
		ret[j] = temp;
	}
	return ret;
}
// A helper function to get birthday
string* get_birth(string i)
{
	string* ret = new string[3];
	int counter = 0;
	for (int j = 0; j < 3; j++)
	{
		string temp = "";
		while (i[counter] != '\0')
		{
			if (i[counter] == '/')
			{
				counter++;
				break;
			}
			temp += i[counter];
			counter++;
		}
		ret[j] = temp;
	}
	return ret;
}
//time_t tm2time(int month, int day, int year, int hour = 0, int minute = 0, int second = 0)
//{
//	tm date;
//	date.tm_year = year;
//	date.tm_mon = month;
//	date.tm_mday = day;
//	date.tm_hour = hour;
//	date.tm_min = minute;
//	date.tm_sec = second;
//	return mktime(&date);
//}

//key function 
//
// LoadList -- load file into Listnode
//   INPUTS: 
//    有一些关于指针索引转换的bug让我很困惑，可能是fstream 库本身的问题
//   有可能无法封装成函数，要在主函数里像学长一样暴力去解
//   写完ECE210再看看
//   OUTPUTS: a txt file com
//            
//   RETURN VALUE: 0 for success, 1 for failing
//   SIDE EFFECTS: mark each graph vertex in g with 
//           a minimap bit number based on p
//
int LoadList(string filename, ListNode* List,time_t current_time) {
	string str;
	ifstream myfile;
	myfile.open(filename);
	while (!myfile.eof()) {//number是行数
		getline(myfile, str);
		string* line = split(str);
		ListNode NEW;
		int ID = atoll(line[0].c_str());
		int profession = atoll(line[6].c_str());
		int risk = atoll(line[8].c_str());

		int month = atoll((get_birth(line[7])[0].c_str()));
		int day = atoll((get_birth(line[7])[1].c_str()));
		int year = atoll((get_birth(line[7])[2].c_str()));

		int birth = tm2time(month, day, year);

		NEW.setRecordID(ID);
		NEW.setRecordName(line[1]);
		NEW.setRecordAddress(line[2]);
		NEW.setRecordPhone(line[3]);
		NEW.setRecordWeChat(line[4]);
		NEW.setRecordEmail(line[5]);
		NEW.setRecordProfession(profession);
		NEW.setRecordBirth(birth,current_time);
		NEW.setRecordRisk(risk);

		List->append(&NEW);
	}
	return 0;
}


//int main() {
//	// Define a register place
//
//	cout << "Hello" << endl;
//
//	cout << "Enter a to start the Vacancine Program, enter q to quit" << endl;
//
//
//
//	// Function variables
//	int withdraw_mod = 0;
//
//	// Time variables
//	int half_day = 0; //Initialize the timeline recorder half_day
//	int week = 1;     //Initialize the timeline recorder week
//	int month = 1;    //Initialize the timeline recorder week
//	// number markers for reporting
//	int reginum = 0;       //Initialize the number of registers
//	int waitnum = 0;       //Initialize the number of waitings
//	int waitnum_total = 0; //Initialize the number of waitings in total
//	int appointnum = 0;    //Initialize the number of appointments
//	int withdrawnum = 0;   //Initialize the number of withdraws
//	int averagetime = 0;   //Initialize the average waiting time
//	// statistics
//	const int registry_capacity = 500; // the capacity of each registration
//
//
//	  // INdependent Files containing patients information in each Resitory 
//	ifstream myfile;
//	ifstream myfile2;
//	ifstream myfile3;
//	// Open, read the information and check whether can we open it
//	myfile.open("INPUT_MID_00.csv");
//	myfile2.open("INPUT_MID_01.csv");
//	myfile3.open("INPUT_MID_02.csv");
//
//	if (!myfile.fail())
//	{
//		cout << "The file INPUT_MID_00.csv can not be opened" << endl;
//		return 0;
//	}
//	if (!myfile2.fail())
//	{
//		cout << "The file INPUT_MID_01.csv can not be opened" << endl;
//		return 0;
//	}
//	if (!myfile3.fail())
//	{
//		cout << "The file INPUT_MID_02.csv can not be opened" << endl;
//		return 0;
//	}
//	// Put into List
//
//	ListNode tmp;
//	ListNode* List = &tmp;
//	//ifstream *file1 = &myfile1;
//	;
//	// LoadList(file1,REG1);
//
//	string str;
//	//ifstream myfile = file;
//	while (!myfile.eof()) {//number是行数
//		getline(myfile, str);
//		string* line = split(str);
//		ListNode NEW;
//		int ID = atoll(line[0].c_str());
//		int profession = atoll(line[6].c_str());
//		int risk = atoll(line[8].c_str());
//
//		int month = atoll((get_birth(line[7])[0].c_str()));
//		int day = atoll((get_birth(line[7])[1].c_str()));
//		int year = atoll((get_birth(line[7])[2].c_str()));
//
//		int birth = tm2time(month, day, year);
//
//		NEW.setRecordID(ID);
//		NEW.setRecordName(line[1]);
//		NEW.setRecordAddress(line[2]);
//		NEW.setRecordPhone(line[3]);
//		NEW.setRecordWeChat(line[4]);
//		NEW.setRecordEmail(line[5]);
//		NEW.setRecordProfession(profession);
//		NEW.setRecordBirth(birth);
//		NEW.setRecordRisk(risk);
//
//		List->append(&NEW);
//	}
//	while (List->getForward() != NULL)
//	{
//		cout << List->getRecordBirth() << endl;
//	}
//
//	ofstream outFile;
//	outFile.open("test.txt", ios::app);
//	cout << "\n-----------------------------\nOUTPUT successfully " << endl;
//
//
//	system("pause");
//	outFile.close();
//
//
//	for (int k = 0; k < 500; k++) { // k代表第几个半天
//
//		// 每一个半天......
//		half_day++;
//		// STEP ONE!
//		// 提取文件数据
//
//
//		if ((half_day == 200)) { //|| (month == 3 && week >=14))
//
//			cout << "All patients have been treated." << endl;
//			myfile.close();
//			myfile2.close();
//			myfile3.close();
//
//			cout << "Logging out";
//			for (auto _ = 0; _ < 6; _++)
//			{
//				Sleep(500);
//				cout << ".";
//			}
//			cout << endl;
//
//
//
//			cout << endl;
//			cout << endl;
//			cout << endl;
//			Sleep(200);
//			cout << "   _______  _                    _              ______               _    _       _                  _ \n";
//			Sleep(200);
//			cout << "  |__   __|| |                  | |            |  ____|             | |  | |     (_)                | |\n";
//			Sleep(200);
//			cout << "     | |   | |__    __ _  _ __  | | __ ___     | |__  ___   _ __    | |  | | ___  _  _ __    __ _   | |\n";
//			Sleep(200);
//			cout << "     | |   | '_ \\  / _` || '_ \\ | |/ // __|    |  __|/ _ \\ | '__|   | |  | |/ __|| || '_ \\  / _` |  | |\n";
//			Sleep(200);
//			cout << "     | |   | | | || (_| || | | ||   < \\__ \\    | |  | (_) || |      | |__| |\\__ \\| || | | || (_| |  |_|\n";
//			Sleep(200);
//			cout << "     |_|   |_| |_| \\__,_||_| |_||_|\\_\\|___/    |_|   \\___/ |_|       \\____/ |___/|_||_| |_| \\__, |  (_)\n";
//			Sleep(200);
//			cout << "                                                                                             __/ |     \n";
//			Sleep(200);
//			cout << "                                                                                            |___/     \n";
//			Sleep(200);
//			cout << endl;
//			cout << endl;
//			cout << endl;
//
//
//			return 1;
//		}
//
//	}
//
//
//
//
//
//
//}
//

