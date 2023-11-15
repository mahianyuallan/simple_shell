#include "main.h"

/**
 * catstr_cd - this is a function that links the message for the changing directory error
 *
 * @sh_data: it shows only relevant data off of the directory
 * @msg: a message that outputs print
 * @error: it gives the output message
 * @ver_str: it is used counter lines
 * Return: shows the error message
 */

char *catstr_cd(dt_shell *sh_data, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, sh_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, sh_data->args[0]);
	_strcat(error, msg);
	if (sh_data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = sh_data->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, sh_data->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * get_error_cd - shows any potential errors in get_cd
 * @sh_data: shows only relevant data off of the directory
 * Return: shows the error message
 */
char *get_error_cd(dt_shell *sh_data)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(sh_data->counter);
	if (sh_data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(sh_data->args[1]);
	}

	length = _strlen(sh_data->av[0]) + _strlen(sh_data->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = catstr_cd(sh_data, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * no_error_found - shows the general error message for command not found
 * @sh_data: shows any relevant counters and arguments
 * Return: shows any relevant error message
 */
char *no_error_found(dt_shell *sh_data)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(sh_data->counter);
	length = _strlen(sh_data->av[0]) + _strlen(ver_str);
	length += _strlen(sh_data->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error,sh_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, sh_data->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * exit_error_shell - shows the error message in the exit function for exit_shell
 * @sh_data: shows arguments and counters that are relevant to the data
 * * Return: shows any relevant error message
 */

char *exit_error_shell(dt_shell *sh_data)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(sh_data->counter);
	length = _strlen(sh_data->av[0]) + _strlen(ver_str);
	length += _strlen(sh_data->args[0]) + _strlen(sh_data->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, sh_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, sh_data->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, sh_data->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
