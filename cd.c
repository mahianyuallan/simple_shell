#include "shell.h"

/**
 * par_cmd - changes directory to parent directory
 *
 * @sh_data: relevant data to env
 *
 * Return: null
 */
void par_cmd(dt_shell *sh_data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	envi_set("OLDPWD", cp_pwd, sh_data);
	dir = sh_data->args[1];
	if (_strcmp(".", dir) == 0)
	{
		envi_set("PWD", cp_pwd, sh_data);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		envi_set("PWD", cp_strtok_pwd, sh_data);
	}
	else
	{
		chdir("/");
		envi_set("PWD", "/", sh_data);
	}
	sh_data->status = 0;
	free(cp_pwd);
}

/**
 * usr_cmd - changes directory to the one named by the user
 *
 * @sh_data: data relevant to the directories
 * Return: null
 */
void usr_cmd(dt_shell *sh_data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = sh_data->args[1];
	if (chdir(dir) == -1)
	{
		err_get(sh_data, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	envi_set("OLDPWD", cp_pwd, sh_data);

	cp_dir = _strdup(dir);
	envi_set("PWD", cp_dir, sh_data);

	free(cp_pwd);
	free(cp_dir);

	sh_data->status = 0;

	chdir(dir);
}

/**
 * prev_cmd - changes directory to the previous
 *
 * @sh_data: relevant data to the env
 * Return: null
 */
void prev_cmd(dt_shell *sh_data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = get_envir("OLDPWD", sh_data->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	envi_set("OLDPWD", cp_pwd, sh_data);

	if (chdir(cp_oldpwd) == -1)
		envi_set("PWD", cp_pwd, sh_data);
	else
		envi_set("PWD", cp_oldpwd, sh_data);

	p_pwd = get_envir("PWD", sh_data->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	sh_data->status = 0;

	chdir(p_pwd);
}

/**
 * source_cmd - changes back to home/source directory
 *
 * @sh_data: relevant data to the env
 * Return: null
 */
void source_cmd(dt_shell *sh_data)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = get_envir("HOME", sh_data->_environ);

	if (home == NULL)
	{
		envi_set("OLDPWD", p_pwd, sh_data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		err_get(sh_data, 2);
		free(p_pwd);
		return;
	}

	envi_set("OLDPWD", p_pwd, sh_data);
	envi_set("PWD", home, sh_data);
	free(p_pwd);
	sh_data->status = 0;
}
