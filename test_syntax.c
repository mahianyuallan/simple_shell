#include "shell.h"

/**
 * char_rep - counts the repetitions of a char
 *
 * @in: in string
 * @m: index
 * Return: repetitions
 */
int char_rep(char *in, int m)
{
	if (*(in - 1) == *in)
		return (char_rep(in - 1, m + 1));

	return (m);
}

/**
 * synt_op_err - finds syntax errors
 *
 * @in: in string
 * @m: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int synt_op_err(char *in, int m, char last)
{
	int count;

	count = 0;
	if (*in == '\0')
		return (0);

	if (*in == ' ' || *in == '\t')
		return (synt_op_err(in + 1, m + 1, last));

	if (*in == ';')
		if (last == '|' || last == '&' || last == ';')
			return (m);

	if (*in == '|')
	{
		if (last == ';' || last == '&')
			return (m);

		if (last == '|')
		{
			count = char_rep(in, 0);
			if (count == 0 || count > 1)
				return (m);
		}
	}

	if (*in == '&')
	{
		if (last == ';' || last == '|')
			return (m);

		if (last == '&')
		{
			count = char_rep(in, 0);
			if (count == 0 || count > 1)
				return (m);
		}
	}

	return (synt_op_err(in + 1, m + 1, *in));
}

/**
 * char_first - finds index of the first char
 *
 * @in: in string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int char_first(char *in, int *m)
{

	for (*m = 0; in[*m]; *m += 1)
	{
		if (in[*m] == ' ' || in[*m] == '\t')
			continue;

		if (in[*m] == ';' || in[*m] == '|' || in[*m] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * synt_print_err - prints when a syntax error is found
 *
 * @sh_data: data structure
 * @in: in string
 * @m: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void synt_print_err(dt_shell *sh_data, char *in, int m, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (in[m] == ';')
	{
		if (bool == 0)
			msg = (in[m + 1] == ';' ? ";;" : ";");
		else
			msg = (in[m - 1] == ';' ? ";;" : ";");
	}

	if (in[m] == '|')
		msg = (in[m + 1] == '|' ? "||" : "|");

	if (in[m] == '&')
		msg = (in[m + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = str_int_ax(sh_data->counter);
	length = _strlen(sh_data->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, sh_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * synt_check_err - intermediate function to
 * find and print a syntax error
 *
 * @sh_data: data structure
 * @in: in string
 * Return: 1 if there is an error. 0 in other case
 */
int synt_check_err(dt_shell *sh_data, char *in)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = char_first(in, &begin);
	if (f_char == -1)
	{
		synt_print_err(sh_data, in, begin, 0);
		return (1);
	}

	i = synt_op_err(in + begin, 0, *(in + begin));
	if (i != 0)
	{
		synt_print_err(sh_data, in, begin + i, 1);
		return (1);
	}

	return (0);
}
