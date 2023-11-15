#include "shell.h"

/**
 * line_rd - Read a line from standard input and return it.
 *
 * @ret_val: Pointer to an integer variable to store the number of bytes read.
 *
 * Return: A pointer to the dynamically allocated buffer containing the
 *         read line, or NULL on failure.
 */

char *line_rd(int *ret_val)
{
	size_t buff_sz;
	char *add;

	add = NULL;
	buff_sz = 0;
	*ret_val = line_get(&add, &buff_sz, stdin);
	return (add);
}
