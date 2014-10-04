#include "catalogmanager.h"
CataMan& CataMan::getInstance(){
	static CataMan instance;
	return instance;
}
CataMan::CataMan(){};
CataMan::~CataMan(){};