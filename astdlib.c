#include "shell.h"

/**
 * length_get - function used to get the length of the number.
 * @n: give int number.
 * Return: length in the number of characters of a number.
 */
int length_get(int i)
{
	unsigned int i1;
	int lenght = 1;

	if (i < 0)
	{
		lenght++;
		i1 = i * -1;
	}
	else
	{
		i1 = i;
	}
	while (i1 > 9)
	{
		lenght++;
		i1 = i1 / 10;
	}

	return (lenght);
}
/**
 * str_int_ax - function that does the conversion of int to a string.
 * @n: give int number
 * Return: the string.
 */
char *str_int_ax(int i)
{
	unsigned int i1;
	int lenght = length_get(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (i < 0)
	{
		i1 = i * -1;
		buffer[0] = '-';
	}
	else
	{
		i1 = i;
	}

	lenght--;
	do {
		*(buffer + lenght) = (i1 % 10) + '0';
		i1 = i1 / 10;
		lenght--;
	}
	while (i1 > 0)
		;
	return (buffer);
}

/**
 * str_int - used for the conversion of a string into an integer.
 * @s: it is used to input a string.
 * Return: integer.
 */
int str_int(char *c)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(c + count) != '\0')
	{
		if (size > 0 && (*(c + count) < '0' || *(c + count) > '9'))
			break;

		if (*(c + count) == '-')
			pn *= -1;

		if ((*(c + count) >= '0') && (*(c + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(c + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
