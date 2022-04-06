#include<iostream>
#include"../head.h"
using namespace std;
#include<string>
#include"Print Functions.cpp"
#include <fstream>
#include <sstream>
#include <cstdlib>

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
 * Version:	    1
 * Creation Date:   04-04-2022
 * Filename:	    Report.h
 * History:
 *
 *		
 */




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
int week_report(FibHeap FHP, int week ){

    int option ,end;
    end = 1;
    cout << "Choose the output mode "<<endl;
    cout<<  "0. Do not sort" <<endl;
    cout<<  "1. Sort by name (from a to z )"<<endl;
    cout<<  "2. Sort by age group(1-8)"<<endl;
    cout<<  "3. Sort by profession(1-7)"<<endl;
    cin>>option;

    switch (option)
    {
    case 0:
        /*  */
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;

    default:
        break;
    }


    ofstream outfile;
    stringstream filename;
    filename<<"Week_"<<week<<"report";
    filename<<".txt";
    string name = filename.str();
    outfile.open(name,ios::app);
    outfile << "---------------------------" << endl;
    outfile << endl;
    outfile << "      Week "<< week << " Report"<<
    outfile << endl;    
    outfile << "---------------------------" << endl<<endl;
    outfile << "---------------------------" << endl;
    outfile << endl;
    outfile << "      Treated People List"<<
    outfile << endl;    
    outfile << "---------------------------" << endl;


    FHP.DISPLAY(); // NEED FUNCTION

    outfile << "---------------------------" << endl;
    outfile << endl;
    outfile << "      Registered people with a set appointment List"<<
    outfile << endl;    
    outfile << "---------------------------" << endl;

    outfile.open(name, ios::app);
    outfile << " ------------------------------------------------------------------------------------------ " << endl;
    outfile << endl;
    outfile << "   The people stored in the Fib_heap without a set appointment during this week\n";
    outfile << endl;
    outfile << " ------------------------------------------------------------------------------------------ " << endl;
    outfile << endl;
    outfile.close();

    FibHeap_report(FHP, week, name);  // NEED FUNCTION 


    outfile.open(name, ios::app);
    outfile << "\n";
    outfile.close();


    if( outfile ==  ){
        cout<< "Failed to print this week's report"<<endl;
        return 1;
    }

    
    return 0;
}



int month_report(FibHeap FHP, int month , int reginum, int waitnum, int waitnum_total, int appointnum, int withdrawnum, int averagetime){
    ofstream outfile;
    stringstream filename;
    filename<<"Month_"<<month<<"report";
    filename<<".txt";
    string name = filename.str();
    outfile.open(name,ios::app);
    outfile << "---------------------------" << endl;
    outfile << endl;
    outfile << "      Month "<< month << " Report"<<
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

    if( == ){
        cout<< "Failed to print this month's report"<<endl;
        return 1;
    }
    return 0;
}


void FibHeap_report(FibHeap<long long> &Fib, int halfday, string filename)
{
    Fib.Display_all(  , filename);  //Pass the variable halfday in main function into the display function of the Fibonacci heap
}

int main(){
    FibHeap H;
    week_report(H,7);

    month_report(H,3);



}


// PS, something about main 

      // 每个登记处有一个专属文件，文件里是病人们的信息
        ifstream myfile1;
        ifstream myfile2;
        ifstream myfile3;
        // 打开五个登记处的文件
        myfile1.open("INPUT_MID_00.csv");
        myfile2.open("INPUT_MID_01.csv");
        myfile3.open("INPUT_MID_02.csv");
 
        if (!myfile1.is_open())
        {
            cout << "The file INPUT_MID_00.csv can not be opened" << endl;
            return 0;
        }
        if (!myfile2.is_open())
        {
            cout << "The file INPUT_MID_01.csv can not be opened" << endl;
            return 0;
        }
        if (!myfile3.is_open())
        {
            cout << "The file INPUT_MID_02.csv can not be opened" << endl;
            return 0;
        }

            int n = myfile1.tellg(); // 文件大小 