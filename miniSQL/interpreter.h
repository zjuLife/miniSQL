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
	int getCmd(string cmd);
	
private:
	string query;		//����
	string opType;
	string objType;		//�� ���� index
	string objName;		//tablename ���� indexname
	void resetQuery();
	int doQuery();
	int formatCMD(string cmd);	//�õ���ʽ�����query�� ��query����
	int execFile(string fileName);

	int doCreate();
	int doDrop();
	int doSelect();
	int doInsert();
	int doDelete();
};
#endif