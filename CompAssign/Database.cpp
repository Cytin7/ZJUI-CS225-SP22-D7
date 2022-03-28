#include "CompAssign.h"


Database::Database()
{
	RecordList old_list;
	RecordList new_list;
	this->old_records = &old_list;
	this->new_records = &new_list;
}

Database::~Database()
{
}

void Database::submit(Database* center)
{
	center->new_records->extend(this->new_records);
	this->merge();
}

void Database::merge()
{
	this->old_records->getDummy()->getBackward()->setForward(this->new_records->getDummy()->getForward());
	this->old_records->getDummy()->setBackward(this->new_records->getDummy()->getBackward());
	this->new_records->getDummy()->getForward()->setBackward(this->old_records->getDummy()->getBackward());
	this->new_records->getDummy()->getBackward()->setForward(this->old_records->getDummy());
	this->new_records->getDummy()->setForward(this->new_records->getDummy());
	this->new_records->getDummy()->setBackward(this->new_records->getDummy());
	this->old_records->setLength(this->old_records->getLength() + this->new_records->getLength());
	this->new_records->setLength(0);
}



