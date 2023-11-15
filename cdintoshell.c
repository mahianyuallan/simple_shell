#include "shell.h"

/**
 * sh_cmd - change directory
 *
 * @sh_data: relevant data
 * Return: 1 if successful, 0 if not
 */
int sh_cmd(dt_shell *sh_data)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = sh_data->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		source_cmd(sh_data);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		prev_cmd(sh_data);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		par_cmd(sh_data);
		return (1);
	}

	usr_cmd(sh_data);

	return (1);
}
