#ifndef _CATALOGMANAGER_H_
#define _CATALOGMANAGER_H_
#include <iostream>
using namespace std;
class CataMan{
public:
	static CataMan& getInstance();
private:
	CataMan();
	~CataMan();

};
#endif