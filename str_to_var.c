#include "shell.h"

/**
 * env_chk - Check for environment variables in the given input.
 *
 * This function checks for environment variables in the given input
 * and adds them to the linked list h.
 *
 * @h: Pointer to the head of the linked list.
 * @in: Input string to check for environment variables.
 * @data: Pointer to the dt_shell structure.
 */
void env_chk(l_var **h, char *in, dt_shell *data)
{
int column = 0, str, m = 1, last_val;
char **_envr = data->_envir;

while (_envr[column])
{
str = 0;
while (_envr[column][str])
{
switch (_envr[column][str])
{
case '=':
last_val = _strlen(_envr[column] + str + 1);
var_add_nd(h, m, _envr[column] + str + 1, last_val);
return;
default:
if (in[m] == _envr[column][str])
m++;
else
break;
}
str++;
}
column++;
}
m = 0;
while (in[m])
{
switch (in[m])
{
case ' ':
case '\t':
case ';':
case '\n':
return;
default:
m++;
}
}

var_add_nd(h, m, NULL, 0);
}

/**
 * var_chk - Check for variables in the given input.
 *
 * This function checks for variables in the given input and adds them
 * to the linked list h. It returns the length of the variable.
 *
 * @h: Pointer to the head of the linked list.
 * @in: Input string to check for variables.
 * @st: String representing the variable.
 * @data: Pointer to the dt_shell structure.
 *
 * Return: Length of the variable.
 */
int var_chk(l_var **h, char *in, char *st, dt_shell *data)
{
int a, last, last_pid;

last = _strlen(st);
last_pid = _strlen(data->pid);

a = 0;
while (in[a])
{
if (in[a] == '$')
{
switch (in[a + 1])
{
case '?':
var_add_nd(h, 2, st, last);
a++;
break;
case '$':
var_add_nd(h, 2, data->pid, last_pid);
a++;
break;
case '\n':
case '\0':
case ' ':
case '\t':
case ';':
var_add_nd(h, 0, NULL, 0);
break;
default:
env_chk(h, in + a, data);
}
}
a++;
}

return (a);
}

/**
 * input_rep - Replace variables in the input string.
 *
 * This function replaces variables in the input string based on the linked
 * list head and returns the new input string.
 *
 * @head: Pointer to the head of the linked list.
 * @in: Original input string.
 * @new_input: Buffer for the new input string.
 * @nlen: Length of the new input string.
 *
 * Return: Pointer to the new input string.
 */
char *input_rep(l_var **head, char *in, char *new_input, int nlen)
{
l_var *index;
int a = 0, m = 0, n;

index = *head;
while (a < nlen)
{
if (in[m] == '$')
{
if (!(index->len_var) && !(index->len_val))
{
new_input[a] = in[m];
m++;
}
else if (index->len_var && !(index->len_val))
{
for (n = 0; n < index->len_var; n++)
m++;
a--;
}
else
{
for (n = 0; n < index->len_val; n++)
{
new_input[a] = index->val[n];
a++;
}
m += (index->len_var);
a--;
}
index = index->next;
}
else
{
new_input[a] = in[m];
m++;
}
a++;
}
return (new_input);
}
/**
 * var_replace - Replace variables in the input string.
 *
 * This function replaces variables in the input\based on the linked
 * list head and returns the new input string. It also frees the original
 *
 * @input: Original input string.
 * @sh_data: Pointer to the dt_shell structure.
 *
 * Return: Pointer to the new input string.
 */

char *var_replace(char *input, dt_shell *sh_data)
{
l_var *head, *index;
char *status, *new_input;
int olen, nlen;

status = str_int_ax(sh_data->status);
head = NULL;
olen = var_chk(&head, input, status, sh_data);
if (head == NULL)
{
free(status);
return (input);
}
index = head;
nlen = 0;
while (index != NULL)
{
nlen += (index->len_val - index->len_var);
index = index->next;
}
nlen += olen;
new_input = malloc(sizeof(char) * (nlen + 1));
new_input[nlen] = '\0';
new_input = input_rep(&head, input, new_input, nlen);
free(input);
free(status);
var_free_list(&head);
return (new_input);
}
