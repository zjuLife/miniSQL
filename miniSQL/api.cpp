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
int API::createTable(string tableName){
	try{
		CataMan::getInstance().createTable(tableName);
	}catch(int errorCode){
		return errorCode;
	}
}
void API::createIndex(string indexName){
}
void API::dropIndex(string indexName){
}
void API::dropTable(string tableName){
}
void API::selectFrom(string tableName){
}
void API::insertInto(string tableName){
}
void API::deleteWhere(string tableName){
}
