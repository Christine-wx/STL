#pragma once
#include<assert.h>
#include<string.h>

//strncpy:�����strcpy,���һ�������������ƿ������ݵĳ��ȣ�
//        ���õȵ�'\0'�Ž���
char* strncpy(char* dest,const char* src, size_t size) 
{
	assert(dest != NULL && src != NULL);
	char* ret = dest;
	while (size--) 
	{
		*dest++ = *src++;
	}

	return ret;
}