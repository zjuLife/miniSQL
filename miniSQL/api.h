#ifndef _API_H_
#define _API_H_
#include <iostream>
#include "catalogmanager.h"
using namespace std;
//API 作为单例模式
class API{
public:
	static API& getInstance();
	int createTable(string& tableName, string& attrStr);
	void createIndex(string& indexName);
	void dropTable(string& tableName);
	void dropIndex(string& indexName);
	void selectFrom(string& tableName);
	void insertInto(string& tableName);
	void deleteWhere(string& tableName);
private:
	API();
	~API();
};

#endif