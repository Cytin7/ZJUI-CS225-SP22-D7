#pragma once
// Multiple head file only include once

// Include libraries
#include <iostream>
#include "time.h"
#include "time_functions.h"

using namespace std;
/*=================================*
 * Function: strjust
 * Created by CYTIN
 *----------------------------
 * Modify inout dir to C++ string
 *==================================*/
string strjust(string str, int len, char c = ' ');

/*=================================*
 * Class: Record
 * Created by CYTIN
 *---------------------
 * Information data of each record
 *==================================*/
class Record
{
// Variables
public:
	int id;                    // id of the patient
	string name;               // name of the patient
	string address;            // family address
	string phone;              // phone number
	string wechat;             // WeChat number
	string email;              // e-mail address
	time_t birth;              // date of birth
	int age;                   // age
	int age_group;             // age group (0~6)
	int profession;            // profession code (0~7)
	int risk;                  // risk status (0~3)
	bool has_ddl;              // if the record has a ddl
	time_t deadline;           // deadline
	int registry;              // register place code
	time_t reg_time;           // regist time
	time_t appoint_time;       // appointment time 
	int hospital;              // appointed hospital code
    int treatment;             // Type of treatment (0~2)
    int status;
    /* status table
     * 0 - Initialize number
     * 1 - Successfully read into registry
     * 2 - get treatment
     * 3 - Withdraw
     */

// Construct and destruct functions
public:
	Record();

	~Record();

public:
	// set Record data by each variable
	void setRecordID(int id);
	void setRecordName(string name);
	void setRecordAddress(string address);
	void setRecordPhone(string phone);
	void setRecordWeChat(string wechat);
	void setRecordEmail(string email);
	void setRecordBirth(time_t birth, time_t current_time);
	void setRecordProfession(int profession);
	void setRecordRisk(int risk);
	void setRecordDeadline(time_t deadline);
	void setRecordnoDeadline();
	void setRecordRegistry(int registry);
	void setRecordRegisterTime(time_t reg_time);
	void setRecordAppointTime(time_t reg_time);
	void setRecordHospital(int hospital);
	void setNoDeadline();
    void setRecordTreatment(int treatment);
	// get Record data by variables
	int getRecordID();
	string getRecordName();
	string getRecordAddress();
	string getRecordPhone();
	string getRecordWeChat();
	string getRecordEmail();
	time_t getRecordBirth();
	int getRecordAge();
	int getRecordAgeGroup();
	int getRecordProfession();
	int getRecordRisk();
	bool getRecordDDLBool();
	time_t getRecordDeadline();
	time_t getRecordRegisterTime();
	int getRecordRegistry();
	time_t getRecordAppointTime();
	int getRecordHospital();
    int getRecordTreatment();
    string recordInfo();
	// deepcopy the node
	Record* deepcopy();
};

// construct functon of class Record
Record::Record()
{
    // initialize all variables
    this->address = "";
    this->age = 0;
    this->age_group = 0;
    this->appoint_time = 0;
    this->birth = 0;
    this->deadline = 0;
    this->email = "";
    this->hospital = 0;
    this->id = 0;
    this->name = "";
    this->phone = "";
    this->profession = 0;
    this->registry = 0;
    this->risk = 0;
    this->has_ddl = false;
    this->deadline = 0;
    this->wechat = "";
    this->treatment = 0;
    this->status = 0;
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

// destruct function of class Record
Record::~Record()
{
}

// set Record data by each variable
void Record::setRecordID(int id)
{
    this->id = id;
    return;
}
void Record::setRecordName(string name)
{
    this->name = name;
    return;
}
void Record::setRecordAddress(string address)
{
    this->address = address;
    return;
}
void Record::setRecordPhone(string phone)
{
    this->phone = phone;
    return;
}
void Record::setRecordWeChat(string wechat)
{
    this->wechat = wechat;
    return;
}
void Record::setRecordEmail(string email)
{
    this->email = email;
    return;
}
void Record::setRecordBirth(time_t birth, time_t current_time)
{
    this->birth = birth;
    this->age = time_diff(current_time, this->birth).tm_year-70;
    if (12 >= this->age && 0 <= this->age) {
        // age group Children
        this->age_group = 0;
    }
    else if (18 >= this->age) {
        // age group Adolescents
        this->age_group = 1;
    }
    else if (35 >= this->age) {
        // age group Young Adults
        this->age_group = 2;
    }
    else if (50 >= this->age) {
        // age group Adults
        this->age_group = 3;
    }
    else if (65 >= this->age) {
        // age group Seniors
        this->age_group = 4;
    }
    else if (75 >= this->age) {
        // age group Elderly People
        this->age_group = 5;
    }
    else if (75 < this->age) {
        // age group Old People
        this->age_group = 6;
    }
    else {
        // age < 0 cause error
        cerr << "Age Error: Patient age cannot be Negative" << endl;
        this->age_group = -1;
    }
    return;
}
void Record::setRecordProfession(int profession)
{
    this->profession = profession;
    return;
}
void Record::setRecordRisk(int risk)
{
    this->risk = risk;
    return;
}
void Record::setRecordDeadline(time_t deadline)
{
    this->has_ddl = true;
    this->deadline = deadline;
    return;
}
void Record::setRecordnoDeadline()
{
    this->has_ddl = false;
    this->deadline = 0;
    return;
}
void Record::setRecordRegistry(int registry)
{
    this->registry = registry;
    return;
}
void Record::setRecordRegisterTime(time_t reg_time)
{
    this->reg_time = reg_time;
    return;
}
void Record::setRecordAppointTime(time_t reg_time)
{
    this->appoint_time = reg_time;
    return;
}
void Record::setRecordHospital(int hospital) {
    this->hospital = hospital;
    return;
}
void Record::setNoDeadline()
{
    this->has_ddl = false;
    this->deadline = 0;
    return;
}
void Record::setRecordTreatment(int treatment)
{
    this->treatment = treatment;
    return;
}

// get Record data by variables
int Record::getRecordID()
{
    return this->id;
}
string Record::getRecordName()
{
    return this->name;
}
string Record::getRecordAddress()
{
    return this->address;
}
string Record::getRecordPhone()
{
    return this->phone;
}
string Record::getRecordWeChat()
{
    return this->wechat;
}
string Record::getRecordEmail()
{
    return this->email;
}
time_t Record::getRecordBirth()
{
    return this->birth;
}
int Record::getRecordProfession()
{
    return this->profession;
}
int Record::getRecordRisk()
{
    return this->risk;
}
int Record::getRecordRegistry()
{
    return this->registry;
}
time_t Record::getRecordRegisterTime()
{
    return this->reg_time;
}
int Record::getRecordAge()
{
    return this->age;
}
int Record::getRecordAgeGroup()
{
    return this->age_group;
}
bool Record::getRecordDDLBool()
{
    return this->has_ddl;
}
time_t Record::getRecordDeadline()
{
    return this->deadline;
}
time_t Record::getRecordAppointTime()
{
    return this->appoint_time;
}
int Record::getRecordHospital()
{
    return this->hospital;
}
int Record::getRecordTreatment() {
    return this->treatment;
}

/*=================================*
 * Method: ListNode::recordInfo
 * Created by CYTIN
 *-----------------------------
 * copy the node, with copied record
 *==================================*/
string Record::recordInfo()
{
    string str;
    str = "| " + strjust(to_string((this)->getRecordID()), 6) + " | ";
    str = str + strjust((this)->getRecordName(), 20) + " | ";
    str = str + strjust((this)->getRecordPhone(), 16) + " | ";
    str = str + strjust((this)->getRecordWeChat(), 12) + " | ";
    str = str + strjust((this)->getRecordEmail(), 40) + " | ";
    str = str + strjust(" "+to_string((this)->getRecordProfession()), 6) + " | ";
    time_t tmp = (this)->getRecordBirth();
    str = str + strjust(date_str(tmp), 16) + " | ";
    str = str + strjust(" "+to_string((this)->getRecordRisk()), 6) + " | ";
    if ((this)->getRecordDDLBool()) {
        tmp = (this)->getRecordDeadline();
        str = str + strjust(date_str(tmp), 16) + " | ";
    }
    else {
        str = str + strjust(" ", 16) + " | ";
    }
    char treat_char = 65+this->treatment;
    str = str + strjust({0x20,treat_char},5)+" | ";
    str = str + strjust((this)->getRecordAddress(), 32) + " | ";
    switch (status) {
        case 0:
            str = str + strjust("???",11)+" |";
            break;
        case 1:
            str = str + strjust("Waiting",11)+" |";
            break;
        case 2:
            str = str + strjust("Treated",11)+" |";
            break;
        case 3:
            str = str + strjust("Withdrawed",11)+" |";
            break;
        default:
            str = str + strjust("",11)+" |";
            break;
    }
    return str;
}