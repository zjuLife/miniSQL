#ifndef _TUPLE_H_
#define _TUPLE_H_
#include "ErrorCode.h"
#include <iostream>
using namespace std;
enum ATTRI_TYPE{
	INT, FLOAT, CHAR
};
class Attribute{
public:
	Attribute();
	~Attribute();
	bool isPrimary();
	bool isUnique();
	bool isNotNull();

	ATTRI_TYPE m_type;
	size_t m_flag;
	size_t m_length;
	string m_name;
};




#endif