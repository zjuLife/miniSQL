//123
#include <iostream>
#include "interpreter.h"
#include "ErrorCode.h"
using namespace std;
//gao
void initialScreen(){
	cout<<"== Welcome into miniSQL =="<<endl;
	cout<<"== version 1.0 =="<<endl;
	cout<<endl;
}
int main(void){

	initialScreen();

	char cmdBuffer[1000];
	int cmdErrorCode = SUCCESS;
	
	Interpreter interpreter;
	
	while(true){
		if(cmdErrorCode== SUCCESS){
			cout<<"miniSQL>";
		}
		else{
			cout<<endl;
			break;
		}
		gets_s(cmdBuffer);
		string cmdLine(cmdBuffer);
		cmdErrorCode = interpreter.getCmd(cmdLine);
	}
	return 0;
}