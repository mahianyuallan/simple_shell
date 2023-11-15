#include "shell.h"

/**
 * err_get - Handle and display error messages based on error code.
 *
 * This function handles and displays error messages based on the provided
 * error code. It also sets the status in the dt_shell structure.
 *
 * @sh_data: Pointer to the dt_shell structure.
 * @val_err: The error code to handle.
 *
 * Return: The error code (val_err).
 */
int err_get(dt_shell *sh_data, int val_err)
{
char *err;
err = NULL;

if (val_err == -1)
{
err = envir_err(sh_data);
}
else if (val_err == 126)
{
err = path_126_err(sh_data);
}
else if (val_err == 127)
{
err = not_found_err(sh_data);
}
else if (val_err == 2)
{
if (_strcmp("exit", sh_data->args[0]) == 0)
{
err = sh_exit_err(sh_data);
}
else if (_strcmp("cd", sh_data->args[0]) == 0)
{
err = get_cmd_err(sh_data);
}
}

if (err)
{
write(STDERR_FILENO, err, _strlen(err));
free(err);
}

sh_data->status = val_err;
return (val_err);
}
