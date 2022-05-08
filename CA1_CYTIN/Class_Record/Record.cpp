#include "Record.h"

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
}

// destruct function of class Record
Record::~Record()
{
}

// set Record data by each variable
void Record::setRecordID(int id)
{
	this->id = id;
}
void Record::setRecordName(string name)
{
	this->name = name;
}
void Record::setRecordAddress(string address)
{
	this->address = address;
}
void Record::setRecordPhone(string phone)
{
	this->phone = phone;
}
void Record::setRecordWeChat(string wechat)
{
	this->wechat = wechat;
}
void Record::setRecordEmail(string email)
{
	this->email = email;
}
void Record::setRecordBirth(time_t birth, time_t current_time)
{
	this->birth = birth;
	this->age = time_diff(current_time, this->birth).tm_year;
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

}
void Record::setRecordProfession(int profession)
{
	this->profession = profession;
}
void Record::setRecordRisk(int risk)
{
	this->risk = risk;
}
void Record::setRecordDeadline(time_t deadline)
{
	this->has_ddl = true;
	this->deadline = deadline;
}
void Record::setRecordnoDeadline()
{
	this->has_ddl = false;
	this->deadline = 0;
}
void Record::setRecordRegistry(int registry)
{
	this->registry = registry;
}
void Record::setRecordRegisterTime(time_t reg_time)
{
	this->reg_time = reg_time;
}
void Record::setRecordAppointTime(time_t reg_time)
{
	this->appoint_time = appoint_time;
}
void Record::setRecordHospital(int hospital) {
	this->hospital = hospital;
}
void Record::setNoDeadline()
{
	this->has_ddl = false;
	this->deadline = 0;
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

// deepcopy the node
Record* Record::deepcopy()
{
	Record new_record;
	new_record.id = this->id;
	new_record.name = this->name;
	new_record.address = this->address;
	new_record.phone = this->phone;
	new_record.wechat = this->wechat;
	new_record.email = this->email;
	new_record.birth = this->birth;
	new_record.age = this->age;
	new_record.age_group = this->age_group;
	new_record.profession = this->profession;
	new_record.risk = this->risk;
	new_record.deadline = this->deadline;
	new_record.registry = this->registry;
	new_record.reg_time = this->reg_time;
	new_record.appoint_time = this->appoint_time;
	new_record.hospital = this->hospital;
	return &new_record;
}