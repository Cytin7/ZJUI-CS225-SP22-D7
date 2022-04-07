#include<iostream>
#include"../head.h"

#include<string>
#include <fstream>
#include <sstream>
using std::cin;
using std::cout;

#include<windows.h> // For better report performance
/*  
;=======================================;
|	    Computing Assignment One 	 
|       Worked By Group D7	 
|      Netid: jiew5, ZJUid: 3200112404  
|	       Date: 04-04-2022	 
;=======================================;
 *	
 *	
 *
 * Author:	    WangJie
 * Version:	    1.4
 * Creation Date:   04-04-2022
 * Filename:	    Report.h
 * History:
 *
 *		
 */
int    name_sort(ListNode &treat_list, ListNode &risk_list,ListNode &waiting, ListNode &left_list);
int    age_sort(ListNode &treat_list, ListNode &risk_list,ListNode &waiting, ListNode &left_list);      
int    profession_sort(ListNode &treat_list, ListNode &risk_list,ListNode &waiting, ListNode &left_list);      
void List_report(ListNode &List, string file_name);
int week_report(ListNode &treat_list, ListNode &risk_list,ListNode &waiting, ListNode &left_list, int week);
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




//
// week_report -- The system will produce weekly reports comprising
//          - the people who have been treated including their profession category, age category,
//            risk status and the waiting time from registration to treatment,
//          – the registered people with a set appointment including their profession category, age
//            category, risk status and their waiting time until now,
//          – the queueing people without a set appointment including their profession category,
//            age category, risk status and their waiting time until now.
//            
//          Report printing is consist of 3 mode: Sort by Name, Profession or Age Group
//
//   INPUTS: FibHeap FHP
//           int week -- Current Week
//           int 
//   OUTPUTS: a txt file com
//            
//   RETURN VALUE: 0 for success, 1 for failing
//   SIDE EFFECTS: mark each graph vertex in g with 
//           a minimap bit number based on p
//
int week_report(ListNode &treat_list, ListNode &risk_list,ListNode &waiting, ListNode &left_list, int week){
    int option ,end;
    end = 1;
    cout<<endl<< "Choose the output mode "<<endl;
    cout<<  "0. Do not sort" <<endl;
    cout<<  "1. Sort by name (from a to z )"<<endl;
    cout<<  "2. Sort by age group(1-8)"<<endl;
    cout<<  "3. Sort by profession(1-7)"<<endl;
    cin>>option;
    int sign = 0;
    switch (option)
    {
    
    case 1:
        sign = name_sort(treat_list, risk_list, waiting, left_list);
        
        break;
    case 2:
        sign = age_sort(treat_list, risk_list, waiting, left_list);

        break;
    case 3:
        sign = profession_sort(treat_list, risk_list, waiting, left_list);
    
        break;

    default:
        cout<< "Default Mode Start, printing report without sorting."<<endl;
        for (auto _ = 0; _ < 6; _++)
        {
            Sleep(500);
            cout << ".";
        }
        cout << endl;
        break;
    }
    if (sign == 1)
    {
        cout << "Sorry, sort was cracked, restarting soon..."<<endl;
        return 1;
    }
    


    ofstream outfile;
    stringstream filename;
    filename<<"Week_"<<week<<"report";
    filename<<".txt";
    string name = filename.str();
    outfile.open(name,ios::app);
    outfile << "---------------------------" << endl;
    outfile << endl;
    outfile << "      Week "<< week << " Report"<< endl;    
    outfile << "---------------------------" << endl<<endl;
    outfile << "---------------------------" << endl;
    outfile << endl;
    outfile << "      Treated People List"<<   endl;    
    outfile << "---------------------------" << endl;
    outfile.close();

    List_report(treat_list,name); // NEED FUNCTION

    outfile.open(name,ios::app);
    outfile << "---------------------------" << endl;
    outfile << endl;
    outfile << "      Registered people with a set appointment List";
    outfile << endl;    
    outfile << "---------------------------" << endl;
    outfile.close();
    List_report(waiting,name); // NEED FUNCTION

    outfile.open(name, ios::app);
    outfile << " ------------------------------------------------------------------------------------------ " << endl;
    outfile << endl;
    outfile << "   The people stored in the Fib_heap without a set appointment during this week\n";
    outfile << endl;
    outfile << " ------------------------------------------------------------------------------------------ " << endl;
    outfile << endl;
    outfile.close();

    List_report(left_list, name);  // NEED FUNCTION 


    outfile.open(name, ios::app);
    outfile << "\n";
    outfile.close();

    outfile.open(name, ios::app);
    outfile << " ------------------------------------------------------------------------------------------ " << endl;
    outfile << endl;
    outfile << "                              END of Week"<<week<< "report"<<endl;
    outfile << endl;
    outfile << " ------------------------------------------------------------------------------------------ " << endl;
    outfile << endl;
    outfile.close();

    if( outfile.is_open() ){
        cout<< "Failed to print this week's report"<<endl;
        return 1;
    }else{

        cout<< "-----------------------------------------"<<endl;
        cout<< "Sucessfully generate week"<<week<<"report"<<endl;
    
        return 0;
    }
}


//
// month_report -- The system will produce monthly reports comprising
//          - the people who have been treated including their profession category, age category,
//            risk status and the waiting time from registration to treatment,
//          – the registered people with a set appointment including their profession category, age
//            category, risk status and their waiting time until now,
//          – the queueing people without a set appointment including their profession category,
//            age category, risk status and their waiting time until now.
//            
//          Report printing is consist of 3 mode: Sort by Name, Profession or Age Group
//
//   INPUTS: FibHeap FHP
//           int week -- Current Week
//           int 
//   OUTPUTS: a txt file com
//            
//   RETURN VALUE: 0 for success, 1 for failing
//   SIDE EFFECTS: mark each graph vertex in g with 
//           a minimap bit number based on p
//

/*
Writing to a file is just redirecting the output to the file. 
See slide 22 of Lab2.pdf using ofstream (there's a typo) and pages 502/503 in the C++ textbook you find on BB.
This is only a minor C++ issue.*/

//You count those who are waiting for each registration office, and the total number for all registration offices together.

int month_report(ListNode &List, int month , int reginum, int waitnum, int waitnum_total, int appointnum, int withdrawnum, int averagetime){
    ofstream outfile;
    stringstream filename;
    filename<<"Month_"<<month<<"report";
    filename<<".txt";
    string name = filename.str();
    outfile.open(name,ios::app);
    outfile << "---------------------------" << endl;
    outfile << endl;
    outfile << "      Month " << month << " Report";
    outfile << endl;    
    outfile << "---------------------------" << endl;



    outfile << "The number of people registered:   ";
    outfile << reginum << "." << endl;
    outfile << "The number of registered people who are waiting:   ";
    outfile << waitnum << "." << endl;
    outfile << "Total number of people who are waiting:    ";
    outfile << waitnum_total << "." << endl;
    outfile << "Number of treatment appointments been made:    ";
    outfile << (appointnum) << "." << endl;
    outfile << "The average waiting time:  ";
    outfile << (averagetime / 2) << " days." << endl;
    outfile << "The number of people who withdrew: ";
    outfile << (withdrawnum) << "." << endl;
    outfile.close();


    outfile << "-------------------------------------------" << endl;
    outfile << endl;
    outfile << "      Here is the end of Month Report" <<endl;
    outfile << endl;    
    outfile << "-------------------------------------------" << endl;


    if( outfile.is_open() ){
        cout<< "Failed to print this month's report"<<endl;
        return 1;
    }else{

        cout<< "-----------------------------------------"<<endl;
        cout<< "Sucessfully generate month"<<month<<"report"<<endl;
    
        return 0;
    }
}


// Load everything in a node into the file
void List_report(ListNode &List, string file_name){
    fstream outfile;
    outfile.open(file_name,ios::app);
    if(!List.isDummy()){
        cout << "You should start from Dummy node!" <<endl;
        return;
    }
    ListNode *TEMP;
    ListNode index = List ;
    
    while (index.getForward() !=NULL )
    {// GO THROUGH the whole list 
    // whether need to go dummy?
    // how to arrange
    
    
    int capacity = List.getCapacity();
    time_t birth = List.getRecordBirth();
    string birthday = DatetimeToString(birth);

    int profession = List.getRecordProfession();
    string P = genProfRome(profession);

    int ID = List.getRecordID();
    string Name = List.getRecordName();
    string Address = List.getRecordAddress();
    int Age = List.getRecordAge();
    int AgeGroup = List.getRecordAgeGroup();
    string phone = List.getRecordPhone();
    string wechat = List.getRecordWeChat();
    string email =  List.getRecordEmail();
    int risk = List.getRecordRisk();

    outfile << "   id: " << ID << endl;
    outfile << "   name: " << Name << endl;
    outfile << "   address(registration): " << Address << endl;
    outfile << "   phone number: " << phone << endl;
    outfile << "   WeChat: " << wechat << endl;
    outfile << "   email: " << email << endl;
    outfile << "   profession: " << P << endl;
    outfile << "   birthday: " << birthday << endl;
    outfile << "   treat status: " << "WRONG" << endl;
    outfile <<endl;
    }     
}


/*
void Hospital_report(FibHeap Fib1, ListNode* Hospital){
// Useless, for future development

}
*/

int    name_sort(ListNode &treat_list, ListNode &risk_list,ListNode &waiting, ListNode left_list){
    // TODO
    return 1;
}
int    age_sort(ListNode &treat_list, ListNode &risk_list,ListNode &waiting, ListNode left_list){
    // TODO
    return 1;
}     
int    profession_sort(ListNode &treat_list, ListNode &risk_list,ListNode &waiting, ListNode left_list){
        // TODO
    return 1;
}

int main(){
    FibHeap H;
    

  



}


