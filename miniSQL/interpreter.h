#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <strstream>
using namespace std;
class Interpreter{
public:
	Interpreter();
	~Interpreter();
	int getCmd(string& cmd);
	
private:
	string query;		//内容
	string opType;
	string objType;		//表 还是 index
	string objName;		//tablename 或者 indexname
	void resetQuery();
	int doQuery();
	int formatCMD(string& cmd);	//得到格式化后的query串 和query类型
	int execFile(string& fileName);

	int doCreate();
	int doDrop();
	int doSelect();
	int doInsert();
	int doDelete();
};
#endif