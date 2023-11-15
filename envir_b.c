#include "shell.h"

/**
 * info_copy - Create a new environment variable string.
 *
 * This function creates a new string containing the environment variable
 * name and value in the format "name=value". It returns the newly created string.
 *
 * @name: The name of the environment variable.
 * @value: The value of the environment variable.
 *
 * Return: A newly allocated string containing "name=value".
 */
char *info_copy(char *name, char *value)
{
int l_val, l_name, ln;
char *latest;

l_name = _strlen(name);
l_val = _strlen(value);

ln = l_name + l_val + 2;
latest = malloc(sizeof(char) * (ln));
_strcpy(latest, name);
_strcat(latest, "=");
_strcat(latest, value);
_strcat(latest, "\0");

return (latest);
}

/**
 * envi_set - Set or update an environment variable.
 *
 * This function sets or updates the value of an environment variable.
 * If the variable does not exist, it is created.
 *
 * @name: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * @sh_data: Pointer to the dt_shell structure.
 */
void envi_set(char *name, char *value, dt_shell *sh_data)
{
int m;
char *env_var, *env_name;

m = 0;

while (sh_data->_envir[m])
{
env_var = _strdup(sh_data->_envir[m]);
env_name = _strtok(env_var, "=");

if (_strcmp(env_name, name) == 0)
{
free(sh_data->_envir[m]);
sh_data->_envir[m] = info_copy(env_name, value);
free(env_var);
return;
}
free(env_var);

m++;
}

sh_data->_envir = _reallocdp(sh_data->_envir, m, sizeof(char *) * (m + 2));
sh_data->_envir[m] = info_copy(name, value);
sh_data->_envir[m + 1] = NULL;
}

/**
 * _st_env - Execute the setenv command.
 *
 * This function executes the setenv command, which sets or updates an
 * environment variable with the provided name and value.
 *
 * @sh_data: Pointer to the dt_shell structure.
 *
 * Return: Always returns 1.
 */
int _st_env(dt_shell *sh_data)
{
if (sh_data->args[1] == NULL || sh_data->args[2] == NULL)
{
err_get(sh_data, -1);
return (1);
}

envi_set(sh_data->args[1], sh_data->args[2], sh_data);
return (1);
}

/**
 * _unst_env - Execute the unsetenv command.
 *
 * This function executes the unsetenv command, which removes an environment
 * variable with the provided name.
 *
 * @sh_data: Pointer to the dt_shell structure.
 *
 * Return: Always returns 1.
 */
int _unst_env(dt_shell *sh_data)
{
char *env_var, *env_name;
int a, b, c;
char **envi_realloc;

if (sh_data->args[1] == NULL)
{
err_get(sh_data, -1);
return (1);
}

c = -1;
a = 0;

while (sh_data->_envir[a])
{
env_var = _strdup(sh_data->_envir[a]);
env_name = _strtok(env_var, "=");

if (_strcmp(env_name, sh_data->args[1]) == 0)
{
c = 1;
}
free(env_var);

a++;
}
if (c == -1)
{
err_get(sh_data, -1);
return (1);
}
envi_realloc = malloc(sizeof(char *) * (a));

a = b = 0;
while (sh_data->_envir[a])
{
if (a != c)
{
envi_realloc[b] = sh_data->_envir[a];
b++;
}
a++;
}
envi_realloc[b] = NULL;
free(sh_data->_envir[c]);
free(sh_data->_envir);
sh_data->_envir = envi_realloc;
return (1);
}
