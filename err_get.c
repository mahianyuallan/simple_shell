#include "shell.h"



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
