#include<stdio.h>

int main() 
{
	char src[] = "hello, I am data!";
	char dest[1024];

	//strcpy(dest, src);
	//strncpy(dest, src, 18);
	memcpy(dest, src, 18);
	printf("data : %s\n", dest);


	return 0;
}