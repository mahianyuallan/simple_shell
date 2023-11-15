#include "shell.h"

/**
 * set_line - Set the value of a line pointer with dynamic resizing.
 *
 * @l_ptr: Pointer to the line buffer or NULL.
 * @n: Pointer to the size_t variable storing the size of the line buffer.
 * @buff_size: Pointer to the buffer containing the new line.
 * @m: Size to be accommodated in the line buffer.
 *
 * Return: No explicit return value. The result is stored in 'l_ptr' and 'n'.
 */


void set_line(char **l_ptr, size_t *n, char *buff_size, size_t m)
{

	if (*l_ptr == NULL)
	{
		if  (m > BUFF)
		{
			*n = m;
		}
		else
		{
			*n = BUFF;
		}
		*l_ptr = buff_size;
	}
	else if (*n < m)
	{
		if (m > BUFF)
		{
			*n = m;
		}
		else
		{
			*n = BUFF;
		}
		*l_ptr = buff_size;
	}
	else
	{
		_strcpy(*l_ptr, buff_size);
		free(buff_size);
	}

}


/**
 * line_get - Read a line from a stream and dynamically allocate memory.
 *
 * @l_ptr: Pointer to the line buffer or NULL.
 * @n: Pointer to the size_t variable storing the size of the line buffer.
 * @stream: Pointer to the FILE stream from which to read the line.
 *
 * Return: The number of bytes read, including the newline character,
 * or -1 on failure.
 */

ssize_t line_get(char **l_ptr, size_t *n, FILE *stream)
{
	ssize_t val;
	char t = 'z';
	int m;
	char *buff_size;
	static ssize_t in;

	if (in == 0)
		fflush(stream);
	else
		return (-1);
	in = 0;
	buff_size = malloc(sizeof(char) * BUFF);
	if (buff_size == 0)
	{
		return (-1);
	}
	for (; t != '\n'; in++)
	{
		m = read(STDIN_FILENO, &t, 1);
		if (m == -1 || (m == 0 && in == 0))
		{
			free(buff_size);
			return (-1);
		}
		if (m == 0 && in != 0)
		{
			in++;
			break;
		}
		if (in >= BUFF)
			buff_size = _realloc(buff_size, in, in + 1);
		buff_size[in] = t;
	}
	buff_size[in] = '\0';

	set_line(l_ptr, n, buff_size, in);

	val = in;
	if (m != 0)
	{
		in = 0;
	}
	return (val);
}
