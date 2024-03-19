#pragma once
#include<assert.h>
#include<string.h>
//memcpy: 应用广泛，根据字节数拷贝数据
//        效率高，安全
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