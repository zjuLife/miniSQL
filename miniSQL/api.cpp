#include "api.h"
API::API(){
}
API::~API(){
}
API& API::getInstance(){
	static API instance;	//静态单例
	return instance;
}

/*
FIXME:
采用  异常  返回执行后的错误结果
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
