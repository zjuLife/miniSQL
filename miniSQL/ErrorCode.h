#ifndef _ERRORCODE_H_
#define _ERRORCODE_H_

#define NAME_LENGTH 20	//名字的长度

/***********     catalog Mnanager的标志            *************/

#define CATALOG_HAS_NEXT 0x01
#define CATALOG_IS_INDEX 0x02
#define CATALOG_IS_NOT_NULL 0x04
#define CATALOG_IS_UNIQUE 0x08
#define CATALOG_IS_PRIMARY_KEY 0x10
#define CATALOG_HAS_INDEX 0x20
#define CATALOG_HAS_PRIMARY_KEY 0x40
#define CATALOG_SPACE_USED 0x80

/***********	Attribute 每个元的属性  *************/
#define ATTRI_PRIMARY 0x1
#define ATTRI_UNIQUE 0x2
#define ATTRI_NOT_NULL 0x4
#define ATTRI_INDEX 0x8

/***********	类型 对应的数值标号  *****************/
#define INT_TYPE 0
#define CHAR_TYPE 1
#define FLOAT_TYPE 2
#define INT_LENGTH 4
#define FLOAT_LENGTH 4


//success  0x0000
#define SUCCESS		0x0001		//成功
#define EMPTYSTRING 0x0002		//空输入

#define FAIL 0X1000


	
//Create table 0x1xxx
#define TABLE_EXIST 0x1001

//Drop table 0x2xxx
//#define DROPTABLERROR 0x2000
#define TABLE_NOT_EXIST 0x2001


//Create index 0x3xxx
#define KEY_NOT_UNIQUE 0x3001
#define KEY_NOT_EXIST 0x3002
#define INDEX_EXIST_ON_KEY 0x3003
#define INDEX_NAME_CONFLICT 0x3004

//Drop index 0x4xxx
#define INDEX_NOT_EXIST 0x4001




#define SYNTAXERROR 0x7000		//语法失败

#define FILENOTFOUND	0x8000		//打开文件失败
#define FILEEXE		0x8001		//8001 - FFFE保留
								//错误码&7FFF后 得到行号

//Select

//Insert


//Delete

//Quit
#define QUITMINISQL 0xFFFF		//退出

#endif