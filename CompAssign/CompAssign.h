#pragma once
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

// functions
string genProfRome(const int& prof);

/*  // Double linked list node
	// 双向链表结构节点
	class DNode
	{
	protected:
		DNode* forward;
		DNode* backward;

	public:
		DNode();
		~DNode();
		DNode* setForward(DNode* forward);
		DNode* setBackward(DNode* backward);
		DNode* getForward();
		DNode* getBackward();
		DNode* deepcopy();
	private:

	};
*/

// data for the records
// 记录中保存的数据
class Record
{
protected:
	// identification number
	unsigned int id;
	// name
	string name;
	// contact details
	string address;
	string phone;
	string WeChat;
	string email;
	// profession categories I to VIII
	// prof_code = (uint8_t)0x1 << (8-profession)
	int profession;
	uint8_t prof_code;
	// date of birth
	time_t birth;
	unsigned int age;
	// risk status from 0 to 3
	// risk = (uint8_t)0x1 << risk_value
	int risk;
	uint8_t risk_code;
	// time stamp
	time_t time_stamp;
public:
	Record();
	Record(unsigned int id,
		string name = "",
		string address = "",
		string phone = "",
		string WeChat = "",
		string email = "",
		int prof = 1,
		time_t birth = (time_t)0,
		int risk = 0,
		time_t time_stamp = NULL);
	~Record();

	// Set Record Values (Although not required)
	unsigned int setID(const unsigned int& id);
	string setName(const string& name);
	string setAddress(const string& address);
	string setPhone(const string& phone);
	string setWeChat(const string& WeChat);
	string setEmail(const string& email);
	int setProfession(const int& profession);
	time_t setBirth(const time_t& birth);
	int setRisk(const int& risk);

	// get Record data
	unsigned int getID() const;
	string getName() const;
	string getAddress() const;
	string getPhone() const;
	string getWeChat() const;
	string getEmail() const;
	int getProfession() const;
	uint8_t getProfCode() const;
	string getProfRome() const;
	time_t getBirth() const;
	unsigned int getAge() const;
	int getRisk() const;
	uint8_t getRiskCode() const;

	Record* deepcopy()  const;
	// print Record
	void printRecord()  const;
private:
	void calcAge();
	uint8_t calcProfCode();
	uint8_t calcRiskCode();
};

// Node with Record value
// 含记录数据的节点
class RecordNode :public Record
{
protected:
	RecordNode* forward;
	RecordNode* backward;
	bool dummy_bool;


public:
	RecordNode();
	RecordNode(unsigned int id,
		string name = "",
		string address = "",
		string phone = "",
		string WeChat = "",
		string email = "",
		int prof = 1,
		time_t birth = (time_t)0,
		int risk = 0,
		time_t time_stamp = NULL);
	~RecordNode();
	RecordNode* deepcopy() const;

	RecordNode* setForward(RecordNode* forward);
	RecordNode* setBackward(RecordNode* backward);
	RecordNode* getForward() const;
	RecordNode* getBackward() const;
	bool is_dummy() const;
private:

};

// List of Records
// 记录列表
class RecordList:public RecordNode
{
protected:
	int length;

public:
	RecordList();
	~RecordList();

	int getLength() const;
	RecordList* setLength(int length);
	//RecordNode* getDummy() const;

	RecordList* deepcopy() const;
	void printRecords() const;

	RecordNode* append(RecordNode* new_node);
	RecordNode* get(int k) const;
	RecordNode* insert(RecordNode* insert_node, int k);
	RecordNode* take_away(RecordNode* node);
	void delete_node(RecordNode* node);

	RecordList* operator+(RecordNode* new_node);
	RecordList* operator*(RecordList* list2);
	RecordList* extend(RecordList* list2);
	RecordNode* operator[](int k) const;
private:

};

// detabase of hosbitals.
class Database
{
protected:
	RecordList* old_records;
	RecordList* new_records;
public:
	Database();
	~Database();

	void submit(Database* center);

	void merge();


private:

};
