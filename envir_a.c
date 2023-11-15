#include "shell.h"

/**
 * env_nm_comp - Compare a portion of environment variable with a name.
 *
 * This function compares a portion of an environment variable with a name
 * up to the '=' character. It returns the number of characters compared.
 *
 * @env: The environment variable to compare.
 * @name: The name to compare with.
 *
 * Return: The number of characters compared, or 0 if not equal.
 */
int env_nm_comp(const char *env, const char *name)
{
int m;

m = 0;

while (env[m] != '=')
{
if (env[m] != name[m])
{
return (0);
}
m++;
}

return (m + 1);
}

/**
 * get_envir - Get the value of an environment variable.
 *
 * This function retrieves the value of an environment variable by matching
 * the provided name in the given environment array.
 *
 * @name: The name of the environment variable to retrieve.
 * @_envir: The array of environment variables.
 *
 * Return: A pointer to the value of the environment variable.
 */
char *get_envir(const char *name, char **_envir)
{
int m, mv;
char *env_ptr;

mv = 0;
m = 0;
env_ptr = NULL;

while (_envir[m])
{
mv = env_nm_comp(_envir[m], name);

if (mv)
{
env_ptr = _envir[m];
break;
}
m++;
}

return (mv + env_ptr);
}

/**
 * _envir - Print the environment variables.
 *
 * This function prints the environment variables to the standard output.
 *
 * @sh_data: Pointer to the dt_shell structure.
 *
 * Return: Always returns 1.
 */
int _envir(dt_shell *sh_data)
{
int m, n;

m = 0;
n = 0;

while (sh_data->_envir[m])
{
while (sh_data->_envir[m][n])
{
n++;
}
write(STDOUT_FILENO, sh_data->_envir[m], n);
write(STDOUT_FILENO, "\n", 1);

m++;
}

sh_data->status = 0;
return (1);
}