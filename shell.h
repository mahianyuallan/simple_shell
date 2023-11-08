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


#define TOK_BUFER 128
#define DELIN_TOK " \t\r\n\a"
#define BUFER 1024






* envir_a.c */
char *get_envir(const char *name, char **_envir);
int _envir(dt_shell *sh_data);



#endif
