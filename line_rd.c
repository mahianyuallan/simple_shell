#include "shell.h"


char *line_rd(int *ret_val)
{
	size_t buff_sz;
	char *add;
	add = NULL;
	buff_sz = 0;
	*ret_val = line_get(&add, &buff_sz, stdin);
	return (add);
}
