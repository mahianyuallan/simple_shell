#include "shell.h"

/**
 * shell_exit - Handle the exit built-in command.
 *
 * @sh_data: Pointer to the dt_shell structure containing shell data.
 *
 * Return: 1 if there was an error, 0 otherwise.
 */

int shell_exit(dt_shell *sh_data)
{

	int len_str, digit, large_val;
	unsigned int stat;


	if (sh_data->args[1] != NULL)
	{

		stat = str_int(sh_data->args[1]);

		digit = _isdigit(sh_data->args[1]);

		len_str = _strlen(sh_data->args[1]);

		large_val = stat > (unsigned int)INT_MAX;

		if (!digit || len_str > 10 || large_val)
		{
			err_get(sh_data, 2);

			sh_data->status = 2;

			return (1);
		}

		sh_data->status = (stat % 256);
	}
	return (0);
}
