#pragma once
// Multiple head file only include once

// Include libraries
#include <iostream>
#include <ctime>

// Include our head files
#include "../Time Functions/Time Functions.h"

using namespace std;

/*========================================*
 * Class: Record
 * -----------------
 * created by CYTIN
 *
 * Introduction:
 *	Store all data of a recoord.
 *========================================*/
class Record
{
	// variables
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
	time_t deadline;           // deadline
	int priority;              // priority, used for the priority queue
	int registry;             // register place code
	time_t reg_time;           // regist time
	time_t appoint_time;       // appointment time
	int hospital;              // appointed hospital code
public:
	Record();
	~Record();

	// set Record data
	void setRecordData(int id, string name, string address, string phone, string wechat, string email, time_t birth, int profession, int risk, int registry,time_t current_time);
	// set Record data by variables
	void setRecordID(int id);
	void setRecordName(string name);
	void setRecordAddress(string address);
	void setRecordPhone(string phone);
	void setRecordWeChat(string wechat);
	void setRecordEmail(string email);
	void setRecordBirth(time_t birth,time_t current_time);
	void setRecordProfession(int profession);
	void setRecordRisk(int risk);
	void setRecordRegistry(int registry);
	void setRecordRegisterTime(time_t reg_time);
	void setRecordHospital(int hospital);

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
	int getRecordRegistry();
	time_t getRecordRegisterTime();
	time_t getRecordDeadline();
	int getRecordPriority();
	time_t getRecordAppointTime();
	int getRecordHospital();

private:

};
