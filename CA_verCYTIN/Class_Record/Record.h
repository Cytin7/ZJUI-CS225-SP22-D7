#pragma once
// Multiple head file only include once

// Include libraries
#include <iostream>

// Include our head files
#include "../time_functions/time_functions.h"

using namespace std;

/*=================================*
 * Class: Record
 * Created by CYTIN
 *---------------------
 * Information data of each record
 *==================================*/
class Record
{
// Variables
protected:
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
	void setRecordRegistry(int registry);
	void setRecordRegisterTime(time_t reg_time);
	void setRecordAppointTime(time_t reg_time);
	void setRecordHospital(int hospital);
	void setNoDeadline();
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

	// deepcopy the node
	Record* deepcopy();
};