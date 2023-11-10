#include "shell.h"


int err_get(dt_shell *sh_data, int val_err)

{
char *err;
err = NULL;  

if (val_err == -1) 
{
    err = error_env(sh_data);
} 
else if (val_err == 126) 
{
    err = error_path_126(sh_data);
}
 else if (val_err == 127) 
 {
    err = error_not_found(sh_data);
} 
else if (val_err == 2) 
{
    if (_strcmp("exit", sh_data->args[0]) == 0) 
	{
        err = error_exit_shell(sh_data);
    } 
	else if (_strcmp("cd", sh_data->args[0]) == 0) 
	{
        err = error_get_cd(sh_data);
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
