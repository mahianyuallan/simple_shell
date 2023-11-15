#include "shell.h"

/**
 * envir_err - this the error output for env.
 * @sh_data: diplays relevant data for counters and arguments
 * Return: the appropriate error message.
 */
char *envir_err(dt_shell *sh_data)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = str_int_ax(sh_data->counter);
	msg = ": Unable to add/remove from envment\n";
	length = _strlen(sh_data->av[0]) + _strlen(ver_str);
	length += _strlen(sh_data->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, sh_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, sh_data->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * path_126_err - function to display error message for path and destination.
 * @sh_data: displays data relevant to counters and arguments.
 *
 * Return: the string that has the error.
 */
char *path_126_err(dt_shell *sh_data)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = str_int_ax(sh_data->counter);
	length = _strlen(sh_data->av[0]) + _strlen(ver_str);
	length += _strlen(sh_data->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, sh_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, sh_data->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
