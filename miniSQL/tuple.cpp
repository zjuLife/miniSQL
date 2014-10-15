#include "tuple.h"
Attribute::Attribute(){
}
Attribute::~Attribute(){
}
bool Attribute::isPrimary(){
	return (m_flag & ATTRI_PRIMARY)!=0;
}
bool Attribute::isUnique(){
	return (m_flag & ATTRI_UNIQUE)!=0;
}
bool Attribute::isNotNull(){
	return (m_flag & ATTRI_NOT_NULL)!=0;
}
