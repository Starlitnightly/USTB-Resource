/*
 * ConfigManager.h
 *
 *  Created on: 2018��7��28��
 *      Author: oftenlin
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_
#define SIZE_FILENAME 50


class ConfigManager {
public:
	ConfigManager(const char *filename) { ConfigFileLoad(filename); };
	~ConfigManager() { ConfigFileFree(); };
	//����ini�ļ����ڴ�

	char gFilename[SIZE_FILENAME];
	char *gBuffer;
	int gBuflen;
	int ConfigFileLoad(const char *filename);
	//�ͷ�ini�ļ���ռ��Դ
	void ConfigFileFree();
	int FindSection(const char *section, char **sect1, char **sect2, char **cont1, char **cont2, char **nextsect);
	//��ȡ�ַ�������������
	int GetString(const char *section, const char *key, char *value, int size, const char *defvalue);
	//��ȡ����ֵ
	int GetInt(const char *section, const char *key, int defvalue);
	//��ȡ������
	double GetDouble(const char *section, const char *key, double defvalue);
	int GetValue(const char *section, const char *key, char *value, int maxlen, const char *defvalue);
	//�����ַ�������valueΪNULL����ɾ����key�����У�����ע��
	int SetString(const char *section, const char *key, const char *value);
	//��������ֵ��baseȡֵ10��16��8���ֱ��ʾ10��16��8���ƣ�ȱʡΪ10����
	int SetInt(const char *section, const char *key, int value, int base = 10);
	//    int iniGetIP(const char *section, const char *key, BasicHashTable *hashtable, int size, const char *defvalue);
};


#endif /* CONFIGMANAGER_H_ */