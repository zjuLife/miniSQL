#include <iostream>
#include "interpreter.h"
#include "ErrorCode.h"
using namespace std;
void initialScreen(){
	cout<<"== Welcome into miniSQL =="<<endl;
	cout<<"== version 1.0 =="<<endl;
	cout<<endl;
}
void showError(int& errorCode){
	switch(errorCode){
	case SUCCESS: cout<<"success!"<<endl; break;
	case SYNTAXERROR: cout<<"syntax error"<<endl; break;
	default: cout<<"uncaught exception"<<endl; break;
	}
}
int main(void){

	initialScreen();

	char cmdBuffer[1000];
	int cmdErrorCode = SUCCESS;
	
	Interpreter interpreter;
	
	while(true){
		if(cmdErrorCode!= QUITMINISQL){
			cout<<"miniSQL>";
		}
		else{
			cout<<endl;
			break;
		}
		gets_s(cmdBuffer);
		string cmdLine(cmdBuffer);
		cmdErrorCode = interpreter.getCmd(cmdLine);
		showError(cmdErrorCode);
	}
	return 0;
}