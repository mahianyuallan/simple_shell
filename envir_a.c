#include "shell.h"



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
	  break
	}
      m++;
    }
  
  return (mv + env_ptr);

}


int _envir(dt_shell *sh_data)
{
int m,n;

  m = 0;
  n = 0;

  while (sh_data->_envir[m])
    {
      while(sh_data->_envir[m][n])
	{
	  n++;
	}
      write(STDOUT_FILENO, sh_data->_envir[m],n);
      write(STDOUT_FILENO, "\n", 1);
      
      m++;
    }
  sh_data->status = 0;
  return (1);

}
