#ifndef _API_H_
#define _API_H_
#include <iostream>
//API 作为单例模式
class API{
public:
	static API& getInstance();
	void createTable();
	void createIndex();
	void dropTable();
	void dropIndex();
	void selectFrom();
	void insertInto();
	void deleteWhere();
private:
	API();
	~API();
	
};

#endif