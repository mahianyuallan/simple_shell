#ifndef SHELL_H
#define SHELL_H



#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>


#define BUFF_TOK 128
#define DELIN_TOK " \t\r\n\a"
#define BUFF 1024


extern char **envir;



typedef struct list_line_s
{
	char *line;
	struct list_line_s *next;
} list_line;



typedef struct inbuilt_s
{
	char *name;
	int (*f)(dt_shell *dtsh);
} inbuilt_t;



typedef struct list_sep_s
{
	char separator;
	struct list_sep_s *next;
} list_sep;



typedef struct dt
{
        char **args;
	int status;
	int counter
	char **_envir;
	char *pid;
        char **av;
	char *input;
} dt_shell;




/* envir_a.c */
char *get_envir(const char *name, char **_envir);
int _envir(dt_shell *sh_data);


/* envir_b.c */
char *info_copy(char *name, char *value);
void envi_set(char *name, char *value, dt_shell *sh_data);
int _st_env(dt_shell *sh_data);
int _unst_env(dt_shell *sh_data);




#endif
