#ifndef _ERRORCODE_H_
#define _ERRORCODE_H_
#define SUCCESS		0x0001		//�ɹ�
#define EMPTYSTRING 0x0002		//������

//Create

//Drop



#define FAIL 		0x1000		//ʧ��

#define DROPTABLERROR 0x2000

#define DROPINDEXERROR 0x2001
#define SYNTAXERROR 0x7000		//�﷨ʧ��

#define FILENOTFOUND	0x8000		//���ļ�ʧ��
#define FILEEXE		0x8001		//8001 - FFFE����
								//������&7FFF�� �õ��к�

#define QUITMINISQL 0xFFFF		//�˳�
#endif