#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class Interpreter{
public:
	Interpreter();
	~Interpreter();
	int getCmd(string cmd);
	
private:
	string query;
	string opType;
	void resetQuery();
	int doQuery();
	void formatCMD(string cmd);	//得到格式化后的query串 和query类型
	int execFile(string fileName);
};
#endif