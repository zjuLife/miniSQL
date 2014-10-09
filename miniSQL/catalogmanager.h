#ifndef _CATALOGMANAGER_H_
#define _CATALOGMANAGER_H_
#include <iostream>
#include <vector>
using namespace std;
class TableCatalog{

};
class KeyCatalog{

};
class IndexCatalog{

};
class CataMan{
public:
	static CataMan& getInstance();
	void createTableCheck(string& tableName, 
		vector<Attribute> &attributes);
	void createTable(string& tableName, 
		vector<Attribute> &attributes);
private:
	CataMan();
	~CataMan();


};
#endif