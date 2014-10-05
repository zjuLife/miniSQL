//��������  ������ɺ�  ����API class ����
#include "interpreter.h"
#include "ErrorCode.h"
#include "api.h"
using namespace std;
Interpreter::Interpreter(){}
Interpreter::~Interpreter(){}
string trim(string input){
	if(input.empty()){
		return input;
	}
	else{
		int startpos = 0;
		int finishpos = input.length();
		size_t i;
		for(i=0;i<input.length();i++){
			if(input.at(i)!=' '&&input.at(i)!='\t'){
				startpos = i;
				break;
			}
		}
		for(i=input.length()-1;i>0;i--){
			if(input.at(i)!=' '&&input.at(i)!='\t'){
				finishpos = i;
				break;
			}
		}
		input = input.substr(startpos, finishpos-startpos+1);
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
		int resultCode = formatCMD(cmd);
		if(resultCode == SYNTAXERROR)
			return resultCode;
		else{
			resultCode = doQuery();
			resetQuery();
			return resultCode;
		}
	}
}
int Interpreter::doQuery(){
	//TODO:
	if(opType == "create"){
		return doCreate();
	}
	else if(opType == "drop"){
		//table index
		return doDrop();
	}
	else if(opType == "select"){
		return doSelect();//list
	}
	else if(opType == "insert"){
		//list
	return doInsert();
	}
	else if(opType == "delete"){
		//list
		return doDelete();
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
	objType = "";
	objName = "";

}
int Interpreter::execFile(string& fileName){
	//FIXME: not test yet!!!
	ifstream fp;
    fp.open(fileName,ifstream::in);
	if(fp == NULL){
		return FILENOTFOUND;
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
				return FILENOTFOUND+line;
			}
		}
		return SUCCESS;
	}
}
int Interpreter::formatCMD(string& cmd){
	
	int minpos;
	int spacepos = cmd.find_first_of(" ");
	int tabpos = cmd.find_first_of("\t");
	
	if(tabpos == -1&&spacepos == -1){
		minpos = -1;
	}
	else if(tabpos == -1){
		minpos = spacepos;
		
	}
	else if(spacepos == -1){
		minpos = tabpos;
	}
	else{
		minpos = (spacepos>tabpos)?tabpos:spacepos;
	}
	if(minpos == -1){
		return SYNTAXERROR;
	}
	else{
		opType = cmd.substr(0, minpos);
		query = cmd.substr(minpos+1, cmd.length()-minpos-1);
		query = trim(query);
		//TODO: format query string
		return SUCCESS;
	}
	
}

/******************************************/
/*
FIXME:
�쳣   ������   ����ֵ��
��������
*/

/*

*/
/*****************************************/
int Interpreter::doCreate(){
	 //cout<<objType<<endl;
	//WARNING: query ��Ҫ��format����֮��format
	if(objType == "table"){
		try{
			API::getInstance().createTable(objName, query);
		}catch(int errorCode){
			return errorCode;
		}
		return SUCCESS;
	}
	else if(objType == "index"){
		try{
			API::getInstance().createIndex(objName);
		}catch(int errorCode){
			return errorCode;
		}
		return SUCCESS;
	}
	else
		return SYNTAXERROR;
}
int Interpreter::doDrop(){
	if(objType == "table"){
		try{
			API::getInstance().dropTable(objName);
		}catch(int errorCode){
			return errorCode;
		}
		return SUCCESS;
	}
	else if(objType == "index"){
		try{
			API::getInstance().dropIndex(objName);
		}catch(int errorCode){
			return errorCode;
		}
		return SUCCESS;
	}
	return 0;
}
int Interpreter::doSelect(){
	return 0;
}
int Interpreter::doInsert(){
	return 0;
}
int Interpreter::doDelete(){
	return 0;
}
