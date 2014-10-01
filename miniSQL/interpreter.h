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
	void formatCMD(string cmd);	//�õ���ʽ�����query�� ��query����
	int execFile(string fileName);
};
#endif