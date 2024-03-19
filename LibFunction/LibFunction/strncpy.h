#pragma once
#include<assert.h>
#include<string.h>

//strncpy:相较与strcpy,添加一个参数用于限制拷贝数据的长度，
//        不用等到'\0'才结束
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