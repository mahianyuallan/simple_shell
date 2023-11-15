#include "shell.h"

/**
 * dt_free - Free allocated memory in dt_shell structure.
 *
 * This function frees the dynamically allocated memory within the dt_shell
 * structure, including the _envir array and pid string.
 *
 * @sh_data: Pointer to the dt_shell structure.
 */
void dt_free(dt_shell *sh_data)

{
	unsigned int m;

	m = 0;

	while (sh_data->_envir[m])
	{
		free(sh_data->_envir[m]);
		m++;
	}

	free(sh_data->_envir);
	free(sh_data->pid);
}

/**
 * dt_set - Initialize dt_shell structure with provided arguments and environment.
 *
 * @sh_data: Pointer to the dt_shell structure.
 * @av: Pointer to the command-line arguments array.
 */
void dt_set(dt_shell *sh_data, char **av)
{
	unsigned int m;

	sh_data->args = NULL;

	sh_data->status = 0;

	sh_data->av = av;

	sh_data->counter = 1;

	sh_data->input = NULL;

	m = 0;
	while (environ[m])
	{
		 m++;
	}

	sh_data->_envir = malloc(sizeof(char *) * (m + 1));

	m = 0;
	while (environ[m])
	{
		sh_data->_envir[m] = _strdup(environ[m]);
		m++;
	}

	sh_data->_envir[m] = NULL;
	sh_data->pid = str_int_ax(getpid());
}

/**
 * main - Entry point for the custom shell program.
 *
 * @ac: Number of command-line arguments.
 * @av: Array of command-line argument strings.
 *
 * Return: The exit status of the shell program.
 */
int main(int ac, char **av)
{
	dt_shell sh_data;

	(void) ac;

	signal(SIGINT, sign_get);

	dt_set(&sh_data, av);

	loop_shl(&sh_data);

	dt_free(&sh_data);

	if (sh_data.status < 0)
	{
		return (255);
	}
	return (sh_data.status);
}
