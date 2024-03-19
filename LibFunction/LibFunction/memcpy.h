#pragma once
#include<assert.h>
#include<string.h>
//memcpy: Ӧ�ù㷺�������ֽ�����������
//        Ч�ʸߣ���ȫ
char* memcpy(char* dest, const char* src, size_t size) 
{
	assert(dest != NULL && src != NULL);
	char* ret = dest;
	if (dest >= src && dest <= src + size - 1) 
	{
		dest = dest + size - 1;
		src = src + size - 1;
		while (size--)
			*dest-- = *src--;
	}
	else 
	{
		while (size--) 
			*dest++ = *src++;
	}

	return ret;
}