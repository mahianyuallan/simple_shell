#include "shell.h"


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
			get_error(sh_data, 2);

			sh_data->status = 2;

			return (1);
		}

		sh_data->status = (stat % 256);
	}
	return (0);
}
