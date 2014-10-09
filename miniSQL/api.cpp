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
int API::createTable(string& tableName, string& attrStr){
	//TODO: attrString to attr Vector
	vector<Attribute> attributes;
	try{
		CataMan::getInstance().createTable(tableName, attributes);
	}catch(int errorCode){
		return errorCode;
	}
}
void API::createIndex(string& indexName){
}
void API::dropIndex(string& indexName){
}
void API::dropTable(string& tableName){
}
void API::selectFrom(string& tableName){
}
void API::insertInto(string& tableName){
}
void API::deleteWhere(string& tableName){
}
