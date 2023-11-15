#include "shell.h"

/**
 * comment_none - Remove comments from the input string.
 *
 * @val: Pointer to the input string.
 *
 * Return: A modified version of the input string with comments removed,
 * or NULL if the input string starts with a '#' character.
 */

char *comment_none(char *val)
{
	int m, to;

	m = 0;
	to = 0;

	while (val[m])
	{
		if (val[m] == '#')
		{
			if (m == 0)
			{
				free(val);
				return (NULL);
			}

			if (val[m - 1] == ' ' || val[m - 1] == '\t' || val[m - 1] == ';')
				to = m;
		}
		m++;
	}

	if (to != 0)
	{
		val = _realloc(val, m, to + 1);
		val[to] = '\0';
	}

	return (val);
}


/**
 * loop_shl - Main loop for the shell.
 *
 * @sh_data: Pointer to the dt_shell structure containing shell data.
 */

void loop_shl(dt_shell *sh_data)
{
	char *in;
	int lp, num;

	lp = 1;

	while (lp == 1)
	{
		write(STDIN_FILENO, "#cisfun$ ", 9);

		in = line_rd(&num);

		if (num != -1)
		{
			in = comment_none(in);
			if (in == NULL)
				continue;

			if (synt_check_err(sh_data, in) == 1)
			{
				sh_data->status = 2;
				free(in);
				continue;
			}
			in = var_replace(in, sh_data);

			lp = cmd_split(sh_data, in);

			sh_data->counter += 1;

			free(in);
		}
		else
		{
			lp = 0;
			free(in);
		}
	}
}
