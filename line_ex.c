#include "shell.h"

/**
 * line_ex - Execute a command based on user input.
 *
 * @sh_data: Pointer to the dt_shell structure containing shell data.
 *
 * Return: 1 if the command is empty, the result of the built-in
 * command execution, or the result of the external command execution.
 */
int line_ex(dt_shell *sh_data)
{
	int (*inbuilt)(dt_shell *sh_data);

if (sh_data->args[0] == NULL)
{
return (1);
}
inbuilt = inbuilt_get(sh_data->args[0]);
if (inbuilt != NULL)
{
return (inbuilt(sh_data));
}
return (exe_cmd(sh_data));
}
