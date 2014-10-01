#include "interpreter.h"
#include "ErrorCode.h"
using namespace std;
Interpreter::Interpreter(){}
Interpreter::~Interpreter(){}
string trim(string input){
	if(input.empty()){
		return input;
	}
	else{
		input.erase(0, input.find_first_not_of(" "));
		input.erase(0, input.find_first_not_of("\t"));
		input.erase(0, input.find_last_not_of("0"));
		input.erase(0, input.find_last_not_of("\t"));
		return input;
	}
}
int Interpreter::getCmd(string origincmd){
	string cmd = trim(origincmd);
	if(cmd == "quit"){
		return QUITMINISQL;
	}
	else if(cmd == ""){
		return EMPTYSTRING;
	}
	else{
		formatCMD(cmd);
		int resultCode = doQuery();
		resetQuery();
		return resultCode;
	}
}
int Interpreter::doQuery(){
	//TODO:
	if(opType == "create"){
		//table index
		return 0;
	}
	else if(opType == "drop"){
		//table index
		return 0;
	}
	else if(opType == "select"){
		return 0;//list
	}
	else if(opType == "insert"){
		//list
	return 0;
	}
	else if(opType == "delete"){
		//list
		return 0;
	}
	else if(opType == "execfile"){
		string fileName;
		//TODO:getfilename
		return execFile(fileName);
	}
	else{
		return SYNTAXERROR;
	}
}
void Interpreter::resetQuery(){
	query = "";
	opType = "";
}
int Interpreter::execFile(string fileName){
	ifstream fp;
    fp.open(fileName,ifstream::in);
	if(fp == NULL){
		return FNOTFOUND;
	}
	else{
		char buf[1000];
		string temp;
		
		int line = 0;
		while(!fp.eof()){
			line++;
			fp.getline(buf,1000);
			temp = buf;
			int resultCode = getCmd(temp);
			if(resultCode!=SUCCESS||resultCode!=EMPTYSTRING){
				return FNOTFOUND+line;
			}
		}
		return SUCCESS;
	}
}
void Interpreter::formatCMD(string cmd){
	
}


