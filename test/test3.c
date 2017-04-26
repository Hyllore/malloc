#include "..//malloc.h"
#include <string.h>
#define M (1024 * 1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr1;
	char *addr3;

	addr1 = (char*)malloc(10000024);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char*)realloc(addr1, 10000025);
	addr3[10000025] = 42;
	print(addr3);
	return (0);
}
