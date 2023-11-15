#include "shell.h"


int (*inbuilt_get(char *cmd))(dt_shell *sh_data)
{
	inbuilt_t inbuilt[] = 
	{
		{ "env", _env },

		{ "exit", shell_exit },

		{ "setenv", _setenv },

		{ "unsetenv", _unsetenv },

		{ "cd", sh_cmd },

		{ "help", get_help },

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
