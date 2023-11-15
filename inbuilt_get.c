#include "shell.h"



int (*inbuilt_get(char *cmd))(dt_shell *sh_data)
{
	inbuilt_t inbuilt[] = 
	{
		{ "env", _envir },

		{ "exit", shell_exit },

		{ "setenv", _st_env },

		{ "unsetenv", _unst_env },

		{ "cd", sh_cmd },

		{ "help", hlp_get },

		{ NULL, NULL }
	};

	
	int m;
	m = 0;

	while (inbuilt[m].name)
	{

		if (_strcmp(inbuilt[m].name, cmd) == 0)
		{
			break;
		}
		m++;
	}

     

	return (inbuilt[m].f);
}
