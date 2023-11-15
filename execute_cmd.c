#include "shell.h"

/**
 * current_dir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int current_dir(char *path, int *m)
{
	if (path[*m] == ':')
		return (1);

	while (path[*m] != ':' && path[*m])
	{
		*m += 1;
	}

	if (path[*m])
		*m += 1;

	return (0);
}

/**
 * _loc - locates a command
 *
 * @cmd: command name
 * @_envir: environment variable
 * Return: location of the command.
 */
char *_loc(char *cmd, char **_envir)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = get_envir("PATH", _envir);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (current_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_exe - determines if is an executable
 *
 * @sh_data: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_exe(dt_shell *sh_data)
{
	struct stat st;
	int i;
	char *input;

	input = sh_data->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	err_get(sh_data, 127);
	return (-1);
}

/**
 * cmd_check_err - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @sh_data: data structure
 * Return: 1 if there is an error, 0 if not
 */
int cmd_check_err(char *dir, dt_shell *sh_data)
{
	if (dir == NULL)
	{
		err_get(sh_data, 127);
		return (1);
	}

	if (_strcmp(sh_data->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			err_get(sh_data, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(sh_data->args[0], X_OK) == -1)
		{
			err_get(sh_data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exe_cmd - executes command lines
 *
 * @sh_data: data relevant (args and input)
 * Return: 1 on success.
 */
int exe_cmd(dt_shell *sh_data)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_exe(sh_data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _loc(sh_data->args[0], sh_data->_envir);
		if (cmd_check_err(dir, sh_data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _loc(sh_data->args[0], sh_data->_envir);
		else
			dir = sh_data->args[0];
		execve(dir + exec, sh_data->args, sh_data->_envir);
	}
	else if (pd < 0)
	{
		perror(sh_data->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	sh_data->status = state / 256;
	return (1);
}
