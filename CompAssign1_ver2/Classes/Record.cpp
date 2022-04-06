#include "../head.h"

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
	this->priority = 0;
	this->profession = 0;
	this->registry = 0;
	this->risk = 0;
	this->wechat = "";
}

// destruct function of class Record
Record::~Record()
{

}

void Record::setRecordData(int id, string name, string address, string phone, string wechat, string email, time_t birth, int profession, int risk, int registry)
{
	setRecordID(id);
	setRecordName(name);
	setRecordAddress(address);
	setRecordPhone(phone);
	setRecordWeChat(wechat);
	setRecordEmail(email);
	setRecordBirth(birth);
	setRecordProfession(profession);
	setRecordRisk(risk);
	setRecordRegistry(registry);
	setRecordRegisterTime(current_time);
}

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
void Record::setRecordBirth(time_t birth)
{
	this->birth = birth;
	this->age = time_diff(&current_time, &this->birth).tm_year;
	if (12 >= this->age) {
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
void Record::setRecordRegistry(int registry)
{
	this->registry = registry;
}
void Record::setRecordRegisterTime(time_t reg_time)
{
	this->reg_time = reg_time;
}

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
	return this.registry;
}
time_t Record::getRecordRegisterTime()
{
	return this.reg_time;
}
int Record::getRecordAge()
{
	return this->age;
}
int Record::getRecordAgeGroup()
{
	return this->age_group;
}
time_t Record::fetRecordDeadline()
{
	return this->deadline;
}
int Record::getRecordPriority()
{
	return this->priority;
}
time_t Record::getRecordAppointTime()
{
	return this->appoint_time;
}
int Record::getRecordHospital()
{
	return this->hospital;
}