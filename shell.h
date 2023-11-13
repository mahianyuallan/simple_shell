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


/*  err_get.c */
int err_get(dt_shell *sh_data, int val_err);


/*  hlp_get.c  */
int hlp_get(dt_shell *sh_data);



/*  inbuilt_get.c  */
int (*inbuilt_get(char *cmd))(dt_shell *sh_data);

/* line_ex.c   */
int line_ex(dt_shell *sh_data);


/*  line_get.c  */
void set_line(char **l_ptr, size_t *n, char *buff_size, size_t m);
ssize_t line_get(char **l_ptr, size_t *n, FILE *stream);



/*  line_rd.c  */
char *line_rd(int *ret_val);



/*  loop_shl.c  */
char *comment_none(char *val);
void loop_shl(dt_shell *sh_data);



/*  replace_var.c  */
void env_chp(l_var **h, char *in, dt_shell *data);
int var_chp(l_var **h, char *in, char *st, dt_shell *data);
char *input_rep(l_var **h, char *input, char *new_input, int len_b);
char *rep_var(char *input, dt_shell *sh_data);


/*  shell_ext.c  */
int shell_exit(dt_shell *sh_data);



/* sign_get.c   */
void sign_get(int val);



/*  split_cmd.c  */
char *char_swp(char *in, int bool);
void new_nodes(list_sep **head_s, list_line **head_l, char *in);
void forward(list_sep **list_s, list_line **list_l, dt_shell *sh_data);
int cmd_split(dt_shell *sh_data, char *in);
char **line_split(char *in);


/*  str_to_var.c  */
void env_chk(l_var **h, char *in, dt_shell *data);
int var_chk(l_var **h, char *in, char *st, dt_shell *data);
char *input_rep(l_var **head, char *in, char *new_input, int nlen);
char *var_rep(char *input, dt_shell *sh_data);

#endif
