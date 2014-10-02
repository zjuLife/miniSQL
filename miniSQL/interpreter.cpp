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
		int startpos = 0;
		int finishpos = input.length();
		int i;
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
}
int Interpreter::execFile(string fileName){
	//FIXME: not test yet!!!
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
int Interpreter::formatCMD(string cmd){
	
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
int Interpreter::doCreate(){
	//WARNING: query 需要在format函数之后format
	strstream tempStr;
	tempStr << query;
	string type;
	tempStr>>type;
	if(type=="table"){

	}
	else if(type=="index"){
	}
	return SUCCESS;
}
int Interpreter::doDrop(){
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
