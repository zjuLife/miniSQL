#include "catalogmanager.h"
CataMan& CataMan::getInstance(){
	static CataMan instance;
	return instance;
}
CataMan::CataMan(){};
CataMan::~CataMan(){};

void CataMan::createTable(string& tableName, vector<Attribute> &attributes){

	TableCatalog tc;
	// ���ú�Ҫд��� table ��Ϣ��CATALOG_HAS_PRIMARY_KEY ��־���Ժ󴴽�����ʱ��ӣ�CATALOG_HAS_INDEX �ڴ�������ʱ��ӣ�
	tc.flag = CATALOG_SPACE_USED;
	tc.flag &= ~CATALOG_HAS_INDEX;
	memset(tc.tableName, 0, NAME_LENGTH);
	strcpy(tc.tableName, tableName.c_str());
	tc.numberOfKeys = attributes.size();
	tc.primaryKey = 0;
	tc.indexFlags = 0;
	// д�� tableCatalog
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

	// keyCatalog �в���δʹ�ÿռ䣬���¿��ռ�
	KeyCatalog kc;
	short currentKeyIndex = -1, previousKeyIndex = 0;
	for (size_t i = 0; i < attributes.size(); i++) {
		// �Ե�ǰ���ԣ����ú�Ҫд��� key ��Ϣ
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
		default: // Ĭ�Ͽ�������Ϊ 255 ���ַ���
			kc.keyType = 1;
			kc.keyLength = 255;
			break;
		}
		kc.nextKey = -1;
		// д�� keyCatalog
		currentKeyIndex++;
		while (currentKeyIndex < (int)keyCatalog.size()
				&& (keyCatalog[currentKeyIndex].flag & CATALOG_SPACE_USED))
			currentKeyIndex++;
		if (currentKeyIndex >= (int)keyCatalog.size())
			// �¿��ռ�
			keyCatalog.push_back(kc);
		else
			// ռ�õ�ǰδʹ�ÿռ�
			keyCatalog[currentKeyIndex] = kc;

		if (i == 0)
			// �����ǰ�ǵ�һ�����ԣ��޸� tableCatalog �� firstKey
			tableCatalog[newTableIndex].firstKey = currentKeyIndex;
		else
			// �����޸Ĵ˱���һ�����Ե� nextKey������ǰ���ǵ�һ�����ԣ�
			keyCatalog[previousKeyIndex].nextKey = currentKeyIndex;

		previousKeyIndex = currentKeyIndex;

		// �����ǰ�������������޸� tableCatalog �ı�־�� primaryKey
		if (kc.flag & CATALOG_IS_PRIMARY_KEY) {
			tableCatalog[newTableIndex].flag |= CATALOG_HAS_PRIMARY_KEY;
			tableCatalog[newTableIndex].primaryKey = i;
		}
	}
}