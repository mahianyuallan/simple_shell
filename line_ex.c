#include "shell.h"


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