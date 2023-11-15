#include "shell.h"


char *line_rd(int *ret_val)
{
	size_t buff_sz;
	char *add;
	add = NULL;
	buff_sz = NULL;
	*ret_val = getline(&input, &buff_sz, stdin);
	return (add);
}
