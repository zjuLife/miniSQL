#include "api.h"
API::API(){
}
API::~API(){
}
API& API::getInstance(){
	static API instance;	//��̬����
	return instance;
}

/*
FIXME:
����  �쳣  ����ִ�к�Ĵ�����
*/
void API::createTable(){
}
void API::createIndex(){
}
void API::dropIndex(){
}
void API::dropTable(){
}
void API::selectFrom(){
}
void API::insertInto(){
}
void API::deleteWhere(){
}
