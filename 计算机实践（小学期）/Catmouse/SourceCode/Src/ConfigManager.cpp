/*
 * ConfigManager.cpp
 * Created on: 2018��7��28��
 * Author: oftenlin
 */


#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ConfigManager.h"

#define  SIZE_LINE  100

#define fmin(x, y)      (x <= y) ? x : y

typedef enum _ELineType_ {
	LINE_IDLE,      //δ������
	LINE_ERROR,     //������
	LINE_EMPTY,     //�հ��л�ע����
	LINE_SECTION,   //�ڶ�����
	LINE_VALUE      //ֵ������
} ELineType;


//ȥ������β�ո�ԭ������д
char *StrStrip(char *s)
{
	size_t size;
	char *p1, *p2;


	size = strlen(s);
	if (!size)
		return s;


	p2 = s + size - 1;


	while ((p2 >= s) && isspace(*p2))
		p2--;
	*(p2 + 1) = '\0';


	p1 = s;
	while (*p1 && isspace(*p1))
		p1++;
	if (s != p1)
		memmove(s, p1, p2 - p1 + 2);
	return s;
}


//�����ִ�Сд�Ƚ��ַ���
int StriCmp(const char *s1, const char *s2)
{
	int ch1, ch2;
	do
	{
		ch1 = (unsigned char)*(s1++);
		if ((ch1 >= 'A') && (ch1 <= 'Z'))
			ch1 += 0x20;


		ch2 = (unsigned char)*(s2++);
		if ((ch2 >= 'A') && (ch2 <= 'Z'))
			ch2 += 0x20;
	} while (ch1 && (ch1 == ch2));
	return(ch1 - ch2);
}

//ȡһ��
//���룺������(ָ�뼰����)
//����������͡���Ч���ݴ�(ȥ��β�ո�)��ע���ס�ע��β����һ����(��β����һ���׼�Ϊ���з�)
//      ��Ч����λ��Ϊ[buf, rem1)
int GetLine(char *buf, int buflen, char *content, char **rem1, char **rem2, char **nextline)
{
	char *cont1, *cont2;
	int cntblank, cntCR, cntLF;     //�����ո񡢻��з�����
	char isQuot1, isQuot2;          //����
	int i;
	char *p;

	//���ȶ��ж�ע�ͣ�֧�����»��з���\r��\n��\r\n��\n\r
	cntblank = 0;
	cntCR = cntLF = 0;
	isQuot1 = isQuot2 = 0;
	cont1 = *rem1 = 0;
	content[0] = 0;
	for (i = 0, p = buf; i < buflen; i++, p++)
	{
		if (*p == 0) {
			p++;
			break;
		}
		//2��CR��LF���н���
		if (cntCR == 2 || cntLF == 2) {
			p--;   //����1
			break;
		}
		//CR��LF��1��֮�������ַ����н���
		if (cntCR + cntLF >= 2) {
			break;
		}
		//CR��LF֮����������ַ����н���
		if ((cntCR || cntLF) && *p != '\r' && *p != '\n')
			break;


		switch (*p) {
		case '\r':
			cntCR++;
			break;
		case '\n':
			cntLF++;
			break;
		case '\'':
			if (!isQuot2)
				isQuot1 = 1 - isQuot1;
			break;
		case '\"':
			if (!isQuot1)
				isQuot2 = 1 - isQuot2;
			break;
		case ';':
		case '#':
			if (isQuot1 || isQuot2)
				break;
			if (*rem1 == NULL)
				*rem1 = p - cntblank;
			break;
		default:
			if (isspace((unsigned char)*p)) {
				cntblank++;
			}
			else {
				cntblank = 0;
				if ((*rem1 == NULL) && (cont1 == NULL))
					cont1 = p;
			}
			break;
		}
	}


	*nextline = p;
	*rem2 = p - cntCR - cntLF;
	if (*rem1 == NULL)
		*rem1 = *rem2;
	cont2 = *rem1 - cntblank;


	if (cont1 == NULL) {
		cont1 = cont2;
		return LINE_EMPTY;
	}


	i = (int)(cont2 - cont1);
	if (i >= SIZE_LINE)
		return LINE_ERROR;


	//����ͷβ���޿ո�
	memcpy(content, cont1, i);
	content[i] = 0;


	if (content[0] == '[' && content[i - 1] == ']')
		return LINE_SECTION;
	if (strchr(content, '=') != NULL)
		return LINE_VALUE;

	return LINE_ERROR;
}

//ȡһ��section
//���룺������
//������ɹ���񡢽������ס�������β���������ס�������β(������)����һ����(��β����һ���׼�Ϊ���л�ע����)
int ConfigManager::FindSection(const char *section, char **sect1, char **sect2, char **cont1, char **cont2, char **nextsect)
{
	int type;
	char content[SIZE_LINE];
	char *rem1, *rem2, *nextline;


	char *p;
	char *empty;
	int uselen = 0;
	char found = 0;

	if (gBuffer == NULL) {
		return 0;
	}

	while (gBuflen - uselen > 0) {
		p = gBuffer + uselen;
		type = GetLine(p, gBuflen - uselen, content, &rem1, &rem2, &nextline);
		uselen += (int)(nextline - p);


		if (LINE_SECTION == type) {
			if (found || section == NULL) break;        //������һsection
			content[strlen(content) - 1] = 0;           //ȥβ��]
			StrStrip(content + 1);                      //ȥ��β�ո�
			if (StriCmp(content + 1, section) == 0) {
				found = 1;
				*sect1 = p;
				*sect2 = rem1;
				*cont1 = nextline;
			}
			empty = nextline;
		}
		else
			if (LINE_VALUE == type) {
				if (!found && section == NULL) {
					found = 1;
					*sect1 = p;
					*sect2 = p;
					*cont1 = p;
				}
				empty = nextline;
			}
	}

	if (!found) return 0;


	*cont2 = empty;
	*nextsect = nextline;
	return 1;
}

//��һ��ȡ����ֵ
//���룺���ݴ�(������д)
//�����������ֵ��
void GetKeyValue(char *content, char **key, char **value)
{
	char *p;

	p = strchr(content, '=');
	*p = 0;
	StrStrip(content);
	StrStrip(p + 1);
	*key = content;
	*value = p + 1;
}

//�ͷ�ini�ļ���ռ��Դ
void ConfigManager::ConfigFileFree()
{
	if (gBuffer != NULL) {
		free(gBuffer);
		gBuffer = 0;
		gBuflen = 0;
	}
}

//����ini�ļ����ڴ�
int ConfigManager::ConfigFileLoad(const char *filename)
{
	FILE *file;
	int len;

	//iniFileFree();
	if (strlen(filename) >= sizeof(gFilename))
		return 0;
	strcpy(gFilename, filename);


	file = fopen(gFilename, "ab+");
	if (file == NULL)
		return 0;


	fseek(file, 0, SEEK_END);
	len = ftell(file);
	gBuffer = (char *)malloc(len);
	if (gBuffer == NULL) {
		fclose(file);
		return 0;
	}


	fseek(file, 0, SEEK_SET);
	len = fread(gBuffer, 1, len, file);
	fclose(file);
	gBuflen = len;
	return 1;
}

//��ȡֵԭʼ��
int ConfigManager::GetValue(const char *section, const char *key, char *value, int maxlen, const char *defvalue)
{
	int type;
	char content[SIZE_LINE];
	char *rem1, *rem2, *nextline;
	char *key0, *value0;


	char *p;
	int uselen = 0;
	char found = 0;
	int len;

	if (gBuffer == NULL || key == NULL) {
		if (value != NULL)
			value[0] = 0;
		return 0;
	}

	while (gBuflen - uselen > 0) {
		p = gBuffer + uselen;
		type = GetLine(p, gBuflen - uselen, content, &rem1, &rem2, &nextline);
		uselen += (int)(nextline - p);


		if (LINE_SECTION == type) {
			if (found || section == NULL) break;        //������һsection
			content[strlen(content) - 1] = 0;           //ȥβ��]
			StrStrip(content + 1);                      //ȥ��β�ո�
			if (StriCmp(content + 1, section) == 0) {
				found = 1;
			}
		}
		else
			if (LINE_VALUE == type) {
				if (!found && section == NULL) {
					found = 1;
				}
				if (!found)
					continue;
				GetKeyValue(content, &key0, &value0);
				if (StriCmp(key0, key) == 0) {
					len = strlen(value0);
					if (len == 0) break;        //��ֵ��Ϊ��Ч
					if (value != NULL) {
						len = fmin(len, maxlen - 1);
						strncpy(value, value0, len);
						value[len] = 0;
					}
					//  printf("value = %s\n",value);
					return 1;
				}
			}
	}

	//δ���ּ�ֵȡȱʡ
	if (value != NULL) {
		if (defvalue != NULL) {
			len = fmin(strlen(defvalue), maxlen - 1);
			strncpy(value, defvalue, len);
			value[len] = 0;
			SetString(section, key, defvalue);
		}
		else {
			value[0] = 0;
		}
	}
	return 0;
}

//��ȡ�ַ�������������
int ConfigManager::GetString(const char *section, const char *key, char *value, int maxlen, const char *defvalue)
{
	int ret;
	int len;

	ret = GetValue(section, key, value, maxlen, defvalue);
	if (!ret)
		return ret;

	//ȥ��β�ո�
	len = strlen(value);
	if (value[0] == '\'' && value[len - 1] == '\'') {
		value[len - 1] = 0;
		memmove(value, value + 1, len - 1);
	}
	else
		if (value[0] == '\"' && value[len - 1] == '\"') {
			value[len - 1] = 0;
			memmove(value, value + 1, len - 1);
		}
	return ret;
}

//��ȡ����ֵ
int ConfigManager::GetInt(const char *section, const char *key, int defvalue)
{
	char valstr[64];


	if (GetValue(section, key, valstr, sizeof(valstr), NULL))
		return (int)strtol(valstr, NULL, 0);
	SetInt(section, key, defvalue, 10);
	return defvalue;
}

//��ȡ������
double ConfigManager::GetDouble(const char *section, const char *key, double defvalue)
{
	char valstr[64];

	if (GetValue(section, key, valstr, sizeof(valstr), NULL))
		return (int)atof(valstr);
	return defvalue;
}

//�����ַ�������valueΪNULL����ɾ����key�����У�����ע��
int ConfigManager::SetString(const char *section, const char *key, const char *value)
{
	FILE *file;
	char *sect1, *sect2, *cont1, *cont2, *nextsect;
	char *p;
	int len, type;
	char content[SIZE_LINE];
	char *key0, *value0;
	char *rem1, *rem2, *nextline;

	if (gBuffer == NULL) {
		return 0;
	}


	if (FindSection(section, &sect1, &sect2, &cont1, &cont2, &nextsect) == 0)
	{
		//δ�ҵ���
		//value��Ч�򷵻�
		if (value == NULL)
			return 0;
		//���ļ�β�����
		file = fopen(gFilename, "ab");
		if (file == NULL)
			return 0;
		fprintf(file, "\r\n[%s]\r\n%s=%s;\r\n", section, key, value);
		fclose(file);
		ConfigFileLoad(gFilename);
		return 1;
	}


	//�ҵ��ڣ�����ڲ���key
	p = cont1;
	len = (int)(cont2 - cont1);
	while (len > 0) {
		type = GetLine(p, len, content, &rem1, &rem2, &nextline);
		if (LINE_VALUE == type) {
			GetKeyValue(content, &key0, &value0);
			if (StriCmp(key0, key) == 0) {
				//�ҵ�key
				file = fopen(gFilename, "wb");
				if (file == NULL)
					return 0;
				len = (int)(p - gBuffer);
				fwrite(gBuffer, 1, len, file);                  //д��key֮ǰ����
				if (value == NULL) {
					//value��Ч��ɾ��
					len = (int)(nextline - gBuffer);            //������ͬע��һ��ɾ��
				}
				else {
					//value��Ч����д
					fprintf(file, "%s=%s", key, value);
					len = (int)(rem1 - gBuffer);                //����β��ԭע��!
				}
				fwrite(gBuffer + len, 1, gBuflen - len, file);  //д��key�����к�ע��֮�󲿷�
				fclose(file);
				ConfigFileLoad(gFilename);
				return 1;
			}
		}


		len -= (int)(nextline - p);
		p = nextline;
	}

	//δ�ҵ�key

	//value��Ч�򷵻�
	if (value == NULL)
		return 0;

	//���ļ�β�����
	file = fopen(gFilename, "wb");
	if (file == NULL)
		return 0;
	len = (int)(cont2 - gBuffer);
	fwrite(gBuffer, 1, len, file);                  //д��key֮ǰ����
	fprintf(file, "%s=%s;\r\n", key, value);
	fwrite(gBuffer + len, 1, gBuflen - len, file);  //д��key֮�󲿷�
	fclose(file);
	ConfigFileLoad(gFilename);
	return 1;
}

//��������ֵ��baseȡֵ10��16��8���ֱ��ʾ10��16��8���ƣ�ȱʡΪ10����
int ConfigManager::SetInt(const char *section, const char *key, int value, int base)
{
	char valstr[64];

	switch (base) {
	case 16:
		sprintf(valstr, "0x%x", value);
		return SetString(section, key, valstr);
	case 8:
		sprintf(valstr, "0%o", value);
		return SetString(section, key, valstr);
	default:    //10
		sprintf(valstr, "%d", value);
		return SetString(section, key, valstr);
	}
}