#ifndef _CATALOGMANAGER_H_
#define _CATALOGMANAGER_H_
#include <iostream>
#include <vector>
using namespace std;

class TableCatalog {
	char flag;
	char tableName[NAME_LENGTH];
	char numberOfKeys; // <= 32
	char primaryKey; // 如果 > 32 表示无主键
	unsigned long indexFlags; // 对每一位，0 表示该键无索引，1 表示该键有索引
	unsigned short firstKey; // key 目录文件中，该表第一条键信息的编号
	short firstIndex; // index 目录文件中，该表第一条索引信息的编号
};
class KeyCatalog {
	char flag;
	char keyName[NAME_LENGTH];
	char keyType; // 键类型，0 表示 int，1 表示 char(n)，2 表示 float
	char keyLength; // 键长度
	short nextKey; // 该表下一条键信息的编号，若无则置 -1
};
class IndexCatalog {
	char flag;
	char indexName[NAME_LENGTH];
	unsigned short onTable; // 该索引所属表在 table 目录文件中的编号
	char key; // 该索引针对所属表的键编号
	short nextIndex; // 该表下一条索引信息的编号，若无则置 -1
};


class CataMan{
public:
	static CataMan& getInstance();
	void tableExistCheck(string& tableName, 
		vector<Attribute> &attributes);
	void createTable(string& tableName, 
		vector<Attribute> &attributes);
	
	

private:
	CataMan() throw(int);
	~CataMan() throw(int);

	void initManager() throw(int);
	void saveManger() throw(int);
	//存所有的table key index信息
	vector<TableCatalog> tableCatalog;
	vector<KeyCatalog> keyCatalog;
	vector<IndexCatalog> indexCatalog;
	void initTableCatalog() throw(int);
	void initKeyCatalog() throw(int);
	void initIndexCatalog() throw(int);

	void saveTableCatalog() throw(int);
	void saveKeyCatalog() throw(int);
	void saveIndexCatalog() throw(int);
};
#endif