#ifndef _API_H_
#define _API_H_
#include <iostream>
using namespace std;
//API 作为单例模式
class API{
public:
	static API& getInstance();
	void createTable(string tableName);
	void createIndex(string indexName);
	void dropTable(string tableName);
	void dropIndex(string indexName);
	void selectFrom(string tableName);
	void insertInto(string tableName);
	void deleteWhere(string tableName);
private:
	API();
	~API();
	
};

#endif