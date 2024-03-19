#pragma once
#include<assert.h>
#include<string.h>

//strcpy:拷贝字符效率高，但是有内存溢出的风险
// 原因：不会判断待拷贝空间的大小，是否大于数据量，拷贝直到
//       遇见'\0'才结束
char* strcpy(char* dest, const char* src) 
{
	assert(*dest != NULL && *src != NULL);

	char* ret = dest;
	while ((*(dest)++ = *(src)++)!='\0');
	return ret;
}