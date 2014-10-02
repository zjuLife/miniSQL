#ifndef _ERRORCODE_H_
#define _ERRORCODE_H_
#define SUCCESS		0x0001		//成功
#define EMPTYSTRING 0x0002		//空输入

//Create

//Drop



#define FAIL 		0x1000		//失败

#define DROPTABLERROR 0x2000

#define DROPINDEXERROR 0x2001
#define SYNTAXERROR 0x7000		//语法失败

#define FILENOTFOUND	0x8000		//打开文件失败
#define FILEEXE		0x8001		//8001 - FFFE保留
								//错误码&7FFF后 得到行号

#define QUITMINISQL 0xFFFF		//退出
#endif