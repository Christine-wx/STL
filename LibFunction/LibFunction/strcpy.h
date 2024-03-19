#pragma once
#include<assert.h>
#include<string.h>

//strcpy:�����ַ�Ч�ʸߣ��������ڴ�����ķ���
// ԭ�򣺲����жϴ������ռ�Ĵ�С���Ƿ����������������ֱ��
//       ����'\0'�Ž���
char* strcpy(char* dest, const char* src) 
{
	assert(*dest != NULL && *src != NULL);

	char* ret = dest;
	while ((*(dest)++ = *(src)++)!='\0');
	return ret;
}