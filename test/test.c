#include <stdio.h>
#include "malloc.h"

int main(void)
{
	int *n = malloc(4);
	printf("%p : %x\n", n, *n);
	int *o = realloc(NULL, 10);
	int *m = realloc(n, 100000);
	*m = ~0;
	free(m);
	n = malloc(10);
	*o = 0x1234;

	puts("");
	printf("%p : %x\n", n, *n);
	printf("%p : %x\n", o, *o);

	return 0;
}
