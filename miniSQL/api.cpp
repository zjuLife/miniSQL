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
