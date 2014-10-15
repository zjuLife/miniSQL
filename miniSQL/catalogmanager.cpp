#include "catalogmanager.h"
CataMan& CataMan::getInstance(){
	static CataMan instance;
	return instance;
}
CataMan::CataMan() throw(int){
	initManager();
}
CataMan::~CataMan() throw(int){
	saveManager();
};
void CataMan::initManager()throw(int){
	//刚打开exe时  初始化3个manager
	loadTableCatalog();
	loadKeyCatalog();
	loadIndexCatalog();
}
void CataMan::saveManager() throw(int){
	saveTableCatalog();
	saveKeyCatalog();
	saveIndexCatalog();
}
/********************加载***********************/
void CataMan::loadTableCatalog() throw(int){
	
	ifstream fin("catalog\\tablecata.dat", ios::binary | ios::ate);
	long size = (long) fin.tellg();
	long num = size / (3 + NAME_LENGTH + sizeof(long) + 2 * sizeof(short));
	fin.seekg(0, ios::beg);
	TableCatalog tc;
	for(int i=0;i<num;i++){
		fin.read(&tc.flag, 1);
		fin.read(tc.tableName, NAME_LENGTH);
		fin.read(&tc.numberOfKeys, 1);
		fin.read(&tc.primaryKey, 1);
		fin.read((char *) &tc.indexFlags, sizeof(long));
		fin.read((char *) &tc.firstKey, sizeof(short));
		fin.read((char *) &tc.firstIndex, sizeof(short));
		tableCatalog.push_back(tc);
		//依次读取所有的 然后放入vector
		//TODO: 这里需要检查 push_back()是push的应用 还是拷贝
	}
	fin.close();
}

void CataMan::loadKeyCatalog() throw(int){
	ifstream fin("catalog\\key.dat", ios::binary | ios::ate);
	long size = (long) fin.tellg();
	//TODO: num 数量的计算
	long num = size / (3 + NAME_LENGTH + sizeof(short));
	fin.seekg(0, ios::beg);

	KeyCatalog kc;

	for (int i = 0; i < num; i++) {
		fin.read(&kc.flag, 1);
		fin.read(kc.keyName, NAME_LENGTH);
		fin.read(&kc.keyType, 1);
		fin.read(&kc.keyLength, 1);
		fin.read((char *) &kc.nextKey, sizeof(short));
		keyCatalog.push_back(kc);
	}
	fin.close();
}
void CataMan::loadIndexCatalog() throw(int){
	ifstream fin("catalog\\index.dat", ios::binary | ios::ate);
	long size = (long) fin.tellg();
	long num = size / (2 + NAME_LENGTH + 2 * sizeof(short));
	fin.seekg(0, ios::beg);

	IndexCatalog ic;

	for (int i = 0; i < num; i++) {
		fin.read(&ic.flag, 1);
		fin.read(ic.indexName, NAME_LENGTH);
		fin.read((char *) &ic.onTable, sizeof(short));
		fin.read(&ic.key, 1);
		fin.read((char *) &ic.nextIndex, sizeof(short));
		indexCatalog.push_back(ic);
	}
	fin.close();
}
/*****************保存*******************/
void CataMan::saveTableCatalog() throw(int){
	ofstream fout("catalog\\talbecata.dat", ios::binary);
	fout.seekp(0, ios::beg);
	for(size_t i=0;i<tableCatalog.size();i++){
		/**
tableCatalog file 格式
		flag 1字节
		name Name_length 要固定一下 
		键数量 1字节  y用char -0号字符的差
		是否有主键 
		indexFlag 每一位 是否索引
		firstKey 第一个键信息
		firstIndex 第一个index信息
		**/
		fout.write(&tableCatalog[i].flag, 1);
		fout.write(tableCatalog[i].tableName, NAME_LENGTH);
		fout.write(&tableCatalog[i].numberOfKeys, 1);
		fout.write(&tableCatalog[i].primaryKey, 1);
		fout.write((char *) &tableCatalog[i].indexFlags, sizeof(long));
		fout.write((char *) &tableCatalog[i].firstKey, sizeof(short));
		fout.write((char *) &tableCatalog[i].firstIndex, sizeof(short));
	}
	fout.close();
}

void CataMan::saveKeyCatalog() throw(int) {
	using namespace std;
	ofstream fout("catalog\\keycata.dat", ios::binary);
	fout.seekp(0, ios::beg);
	for (size_t i = 0; i < keyCatalog.size(); i++) {
		/**
keyCatalog file 格式
		flag  1字节
		name
		键的类型  int char float
		key长度
		下个key的编号
		*/
		fout.write(&keyCatalog[i].flag, 1);
		fout.write(keyCatalog[i].keyName, NAME_LENGTH);
		fout.write(&keyCatalog[i].keyType, 1);
		fout.write((char *) &keyCatalog[i].keyLength, 1);
		fout.write((char *) &keyCatalog[i].nextKey, sizeof(short));
	}
	fout.close();
}
void CataMan::saveIndexCatalog() throw(int) {
	using namespace std;
	ofstream fout("catalog\\indexcata.dat", ios::binary);
	fout.seekp(0, ios::beg);
	for (size_t i = 0; i < indexCatalog.size(); i++) {
		/**
indexCatalog file 格式
		flag 1字节
		name
		所属的表号
		key 1字节
		下个index
		**/
		fout.write(&indexCatalog[i].flag, 1);
		fout.write(indexCatalog[i].indexName, NAME_LENGTH);
		fout.write((char *) &indexCatalog[i].onTable, sizeof(short));
		fout.write(&indexCatalog[i].key, 1);
		fout.write((char *) &indexCatalog[i].nextIndex, sizeof(short));
	}
	fout.close();
}

/**********create table**************/
bool CataMan::tableExistCheck(string &tableName, vector<Attribute> &attributes){
	for(size_t i = 0;i<tableCatalog.size();i++){
		if((tableCatalog[i].flag & CATALOG_SPACE_USED)&&
			!strcmp(tableCatalog[i].tableName, tableName.c_str())){
			/* 如果标记位置1 且名字相同 */
			return true;
		}	
	}
	return false;
}
void CataMan::createTable(string &tableName, vector<Attribute> &attributes){
	tableExistCheck(tableName, attributes);
	TableCatalog tc;
	/**	tc TableCatalog中的信息设置好 **/
	tc.flag = CATALOG_SPACE_USED;
	tc.flag &= ~CATALOG_HAS_INDEX;
	memset(tc.tableName, 0, NAME_LENGTH);
	strcpy(tc.tableName, tableName.c_str());
	tc.numberOfKeys = attributes.size();
	tc.primaryKey = 32;		//WARNING: 初始化为32 表示没有主键！！
	tc.indexFlags = 0;
	
	//写入tableCatalogManager
	short newTableIndex = -1;
	for(size_t i=0;i<tableCatalog.size();i++){
		/* 中途插入空挡 */
		if(!(tableCatalog[i].flag & CATALOG_SPACE_USED)){
			newTableIndex = i;
			tableCatalog[i] = tc;
			break;
		}
	}
	if(newTableIndex == -1){
		/* 添加到最后 */
		tableCatalog.push_back(tc);
		newTableIndex = tableCatalog.size() - 1;
	}

	KeyCatalog kc;
	short currentKeyIndex = -1;
	short previousKeyIndex = 0;
	//存key
	for(size_t i=0;i<attributes.size();i++){
		/* 设置keycatalogman 的信息 */
		kc.flag = CATALOG_SPACE_USED;
		if(attributes[i].isPrimary()){
			kc.flag |= CATALOG_IS_PRIMARY_KEY;
			kc.flag |= CATALOG_IS_UNIQUE;
			kc.flag |= CATALOG_IS_NOT_NULL;
		}
		if(attributes[i].isUnique()){
			kc.flag |= CATALOG_IS_UNIQUE;
		}
		if(attributes[i].isNotNull()){
			kc.flag |= CATALOG_IS_NOT_NULL;
		}
		memset(kc.keyName, 0, NAME_LENGTH);
		//what??????_------------____????*/
		strcpy(kc.keyName, attributes[i].m_name.c_str());
		switch(attributes[i].m_type){
		case INT: //类型判断
			kc.keyType = INT_TYPE;	//0
			kc.keyLength = INT_LENGTH; //4
			break;
		case CHAR:
			kc.keyType = CHAR_TYPE; //1
			//waht??
			kc.keyLength = attributes[i].m_length;
			break;
		case FLOAT:
			kc.keyType = FLOAT_TYPE; //2
			kc.keyLength = FLOAT_LENGTH;	//4
			break;
		default:
			kc.keyType = CHAR_TYPE;	//regard as char
			kc.keyLength = 255;		//max length
			break;
		}
		kc.nextKey = -1;
		currentKeyIndex++;
		//写入KeyCatalog的内存中
		while(currentKeyIndex < (int)keyCatalog.size() &&
			(keyCatalog[currentKeyIndex].flag & CATALOG_SPACE_USED)){
			currentKeyIndex++;
		}
		//找到没有使用的那个
		if(currentKeyIndex >= (int)keyCatalog.size())
			//队列尾
			keyCatalog.push_back(kc);
		else	//否则插入空位置
			keyCatalog[currentKeyIndex] = kc;
		if(i == 0){	//第一条属性
			tableCatalog[newTableIndex].firstKey = currentKeyIndex;
		}
		else{
			keyCatalog[previousKeyIndex].nextKey = currentKeyIndex;
		}
		previousKeyIndex = currentKeyIndex;
		if(kc.flag & CATALOG_IS_PRIMARY_KEY){
			tableCatalog[newTableIndex].flag |= CATALOG_HAS_PRIMARY_KEY;
			tableCatalog[newTableIndex].primaryKey = i;
		}
	}
}