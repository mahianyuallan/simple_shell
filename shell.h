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

extern char **environ;

/**
 * struct list_line_s - Structure for a linked list node holding a line.
 *
 * @line: Pointer to a string representing a line.
 * @next: Pointer to the next node in the linked list.
 */

typedef struct list_line_s
{
	char *line;
	struct list_line_s *next;
} list_line;

/**
 * struct dt - Structure to represent shell data.
 *
 * @args: Array of strings representing command arguments.
 * @status: Integer representing the shell status.
 * @counter: Integer representing the command counter.
 * @_envir: Array of strings representing the environment variables.
 * @pid: String representing the process ID.
 * @av: Array of strings representing command arguments.
 * @input: String representing user input.
 */
typedef struct dt
{
	char **args;
	int status;
	int counter;
	char **_envir;
	char *pid;
	char **av;
	char *input;
} dt_shell;

/**
 * struct inbuilt_s - Structure to represent built-in commands.
 *
 * @name: String representing the name of the built-in command.
 * @f: Function pointer to the corresponding function for the command.
 */
typedef struct inbuilt_s
{
	char *name;
	int (*f)(dt_shell *dtsh);
} inbuilt_t;

/**
 * struct list_sep_s - Structure for a linked list node holding a separator.
 *
 * @separator: Character representing the separator.
 * @next: Pointer to the next node in the linked list.
 */

typedef struct list_sep_s
{
	char separator;
	struct list_sep_s *next;
} list_sep;



/**
 * struct list_l_var - Structure for a linked list node holding a variable.
 *
 * @len_var: Length of the variable name.
 * @val: Pointer to a string representing the variable value.
 * @len_val: Length of the variable value.
 * @next: Pointer to the next node in the linked list.
 */

typedef struct list_l_var
{
	int len_var;
	char *val;
	int len_val;
	struct list_l_var *next;
} l_var;





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
char *var_replace(char *input, dt_shell *sh_data);

/*  aerror1.c */

char *catstr_cd(dt_shell *sh_data, char *msg, char *error, char *ver_str);
char *get_cmd_err(dt_shell *sh_data);
char *not_found_err(dt_shell *sh_data);
char *sh_exit_err(dt_shell *sh_data);

/* aerror2.c */
char *get_alias_err(char **args);
char *envir_err(dt_shell *sh_data);
char *synt_err(char **args);
char *prms_err(char **args);
char *path_126_err(dt_shell *sh_data);


/* ahelp.c */
void envir_help_ax(void);
void envirset_help_ax(void);
void envirunset_help_ax(void);
void gen_help_ax(void);
void exit_help_ax(void);


/* ahelp2.c */

void help_ax(void);
void alias_help_ax(void);
void cmd_help_ax(void);

/* alist.c */
list_sep *separ_add_node(list_sep **head, char separ);
void separ_free_list(list_sep **head);
list_line *line_add_node(list_line **head, char *line);
void free_list_line(list_line **head);

/* alist2.c */
l_var *var_add_nd(l_var **head, int lvar, char *var, int lval);
void var_free_list(l_var **head);





/* amem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);


/* aux_str  */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);


/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void rev_string(char *s);



/* astdlib.c */
int length_get(int i);
char *str_int_ax(int i);
int str_int(char *c);


/* cd.c */
void par_cmd(dt_shell *sh_data);
void usr_cmd(dt_shell *sh_data);
void prev_cmd(dt_shell *sh_data);
void source_cmd(dt_shell *sh_data);

/* cdintoshell.c */
int sh_cmd(dt_shell *sh_data);


/* test_syntax.c */
int char_rep(char *in, int m);
int synt_op_err(char *in, int m, char last);
int char_first(char *in, int *m);
void synt_print_err(dt_shell *sh_data, char *in, int m, int bool);
int synt_check_err(dt_shell *sh_data, char *in);

/* execute_cmd.c */
int current_dir(char *path, int *m);
char *_loc(char *cmd, char **_envir);
int is_exe(dt_shell *sh_data);
int cmd_check_err(char *dir, dt_shell *sh_data);
int exe_cmd(dt_shell *sh_data);


#endif
