#include "catalogmanager.h"
CataMan& CataMan::getInstance(){
	static CataMan instance;
	return instance;
}
CataMan::CataMan(){};
CataMan::~CataMan(){};

void CataMan::createTable(string& tableName, vector<Attribute> &attributes){

	TableCatalog tc;
	// 设置好要写入的 table 信息（CATALOG_HAS_PRIMARY_KEY 标志在稍后创建属性时添加，CATALOG_HAS_INDEX 在创建索引时添加）
	tc.flag = CATALOG_SPACE_USED;
	tc.flag &= ~CATALOG_HAS_INDEX;
	memset(tc.tableName, 0, NAME_LENGTH);
	strcpy(tc.tableName, tableName.c_str());
	tc.numberOfKeys = attributes.size();
	tc.primaryKey = 0;
	tc.indexFlags = 0;
	// 写入 tableCatalog
	short newTableIndex = -1;
	for (size_t i = 0; i < tableCatalog.size(); i++)
		if (!(tableCatalog[i].flag & CATALOG_SPACE_USED)) {
			newTableIndex = i;
			tableCatalog[i] = tc;
			break;
		}
	if (newTableIndex == -1) {
		tableCatalog.push_back(tc);
		newTableIndex = tableCatalog.size() - 1;
	}

	// keyCatalog 中查找未使用空间，或新开空间
	KeyCatalog kc;
	short currentKeyIndex = -1, previousKeyIndex = 0;
	for (size_t i = 0; i < attributes.size(); i++) {
		// 对当前属性，设置好要写入的 key 信息
		kc.flag = CATALOG_SPACE_USED;
		if (attributes[i].isPrimary()) {
			kc.flag |= CATALOG_IS_PRIMARY_KEY;
			kc.flag |= CATALOG_IS_UNIQUE;
			kc.flag |= CATALOG_IS_NOT_NULL;
		}
		if (attributes[i].isUnique())
			kc.flag |= CATALOG_IS_UNIQUE;
		if (attributes[i].isNotNull())
			kc.flag |= CATALOG_IS_NOT_NULL;
		memset(kc.keyName, 0, NAME_LENGTH);
		strcpy(kc.keyName, attributes[i].m_name.c_str());
		switch (attributes[i].m_type) {
		case INT:
			kc.keyType = 0;
			kc.keyLength = 4;
			break;
		case CHAR:
			kc.keyType = 1;
			kc.keyLength = attributes[i].m_length;
			break;
		case FLOAT:
			kc.keyType = 2;
			kc.keyLength = 4;
			break;
		default: // 默认看作长度为 255 的字符串
			kc.keyType = 1;
			kc.keyLength = 255;
			break;
		}
		kc.nextKey = -1;
		// 写入 keyCatalog
		currentKeyIndex++;
		while (currentKeyIndex < (int)keyCatalog.size()
				&& (keyCatalog[currentKeyIndex].flag & CATALOG_SPACE_USED))
			currentKeyIndex++;
		if (currentKeyIndex >= (int)keyCatalog.size())
			// 新开空间
			keyCatalog.push_back(kc);
		else
			// 占用当前未使用空间
			keyCatalog[currentKeyIndex] = kc;

		if (i == 0)
			// 如果当前是第一条属性，修改 tableCatalog 的 firstKey
			tableCatalog[newTableIndex].firstKey = currentKeyIndex;
		else
			// 否则修改此表上一条属性的 nextKey（即当前不是第一条属性）
			keyCatalog[previousKeyIndex].nextKey = currentKeyIndex;

		previousKeyIndex = currentKeyIndex;

		// 如果当前属性是主键，修改 tableCatalog 的标志和 primaryKey
		if (kc.flag & CATALOG_IS_PRIMARY_KEY) {
			tableCatalog[newTableIndex].flag |= CATALOG_HAS_PRIMARY_KEY;
			tableCatalog[newTableIndex].primaryKey = i;
		}
	}
}