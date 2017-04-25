#include "../malloc.h"

int main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
//		show_alloc_mem();
		addr[0] = 42;
		free(addr);
//		show_alloc_mem();
		i++;
	}
//	show_alloc_mem();
	return (0);
}
