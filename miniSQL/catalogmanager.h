#ifndef _CATALOGMANAGER_H_
#define _CATALOGMANAGER_H_
#include <iostream>
#include <vector>
using namespace std;
class Table{

};
class Key{

};
class Index{

};
class CataMan{
public:
	static CataMan& getInstance();
private:
	CataMan();
	~CataMan();
	void createTableCheck(string tableName, 
		vector<Attribute> attributes);
	void createTable(string tableName, 
		vector<Attribute> attributes);

};
#endif