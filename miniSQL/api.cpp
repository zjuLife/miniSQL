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
void API::createTable(string tableName){
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
