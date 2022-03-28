#include "CompAssign.h"

Record::Record()
{
	setID(0);
	setName("");
	setAddress("");
	setPhone("");
	setWeChat("");
	setEmail("");
	setProfession(0);
	setBirth((time_t)0);
	setRisk(0);
}
// construct function with input
Record::Record(unsigned int id,
	string name = "",
	string address = "",
	string phone = "",
	string WeChat = "",
	string email = "",
	int prof = 1,
	time_t birth = (time_t)0,
	int risk = 0,
	time_t time_stamp = NULL)
{
	setID(id);
	setName(name);
	setAddress(address);
	setPhone(phone);
	setWeChat(WeChat);
	setEmail(email);
	setProfession(profession);
	setBirth(birth);
	setRisk(risk);
	if (time_stamp == NULL)
	{
		this->time_stamp = time(NULL);
	}
	else
	{
		this->time_stamp = time_stamp;
	}

}

// set record data
unsigned int Record::setID(const unsigned int& id)
{
	this->id = id;
	return this->id;
}
string Record::setName(const string& name)
{
	this->name = name;
	return this->name;
}
string Record::setAddress(const string& address)
{
	this->address = address;
	return this->address;
}
string Record::setPhone(const string& phone)
{
	this->phone = phone;
	return this->phone;
}
string Record::setWeChat(const string& WeChat)
{
	this->WeChat = WeChat;
	return this->WeChat;
}
string Record::setEmail(const string& email)
{
	this->email = email;
	return this->email;
}
int Record::setProfession(const int& profession)
{
	this->profession = profession;
	this->calcProfCode();
	return this->profession;
}
time_t Record::setBirth(const time_t& birth)
{
	this->birth = birth;
	this->calcAge();
	return this->birth;
}
int Record::setRisk(const int& risk)
{
	this->risk = risk;
	this->calcRiskCode();
	return this->risk;
}

// get Record data
unsigned int Record::getID() const
{
	return this->id;
}
string Record::getName() const
{
	return this->name;
}
string Record::getAddress() const
{
	return this->address;
}
string Record::getPhone() const
{
	return this->phone;
}
string Record::getWeChat() const
{
	return this->WeChat;
}
string Record::getEmail() const
{
	return this->email;
}
int Record::getProfession() const
{
	return this->profession;
}
time_t Record::getBirth() const
{
	return this->birth;
}
int Record::getRisk() const
{
	return this->risk;
}
uint8_t Record::getProfCode() const
{
	return this->prof_code;
}
unsigned int Record::getAge() const
{
	return this->age;
}
uint8_t Record::getRiskCode() const
{
	return this->risk_code;
}

string Record::getProfRome() const
{
	return genProfRome(this->profession);
}

// calculate age using birth
void Record::calcAge()
{
	int birth_year = gmtime(&(this->birth))->tm_year;
	time_t now = time(NULL);
	int year = gmtime(&now)->tm_year;
	this->age = year - birth_year + 1;
	return;
}
// calculate prof_code
uint8_t Record::calcProfCode()
{
	this->prof_code = (uint8_t)0x1 << (8 - this->profession);
	return this->prof_code;
}
//calculate risk_code
uint8_t Record::calcRiskCode()
{
	this->risk_code = (uint8_t)0x1 << (this->risk);
	return this->risk_code;
}



// destruct function
Record::~Record()
{
}

Record* Record::deepcopy()  const
{
	Record new_record(id, name, address, phone, WeChat, email, profession, birth, risk, time_stamp);
	return &new_record;
}

void Record::printRecord()  const
{
	cout << "ID:\t" << id << "\t";
	cout << "Name:\t" << name << "\t";
	cout << "Age:\t" << age << "\t";
	cout << "contact details:" << endl;
	cout << "Phone Number:\t" << phone << "\t";
	cout << "E-mail Address:\t" << email << "\t";
	cout << "WeChat:\t" << WeChat << endl;
	cout << "Address:\t" << address << endl;
	cout << "Birth Date:\t" << birth << "\t";
	cout << "Risk Status:\t" << risk << "\t";
	cout << "Profession Code:\t";
	cout << getProfRome() << endl;

}