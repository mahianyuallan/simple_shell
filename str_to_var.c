#include "shell.h"

void env_chk(l_var **h, char *in, dt_shell *data)
{
	int column, str, m, last_val;
	char **_envr;

	_envr = data->_envir;
	column = 0;
while (_envr[column]) {
    int m = 1;
    int str = 0;

    while (_envr[column][str]) {
        switch (_envr[column][str]) {
        case '=':
            last_val = _strlen(_envr[column] + str + 1);
            add_rvar_node(h, m, _envr[column] + str + 1, last_val);
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

int m = 0;
while (in[m]) {
    switch (in[m]) {
    case ' ':
    case '\t':
    case ';':
    case '\n':
        return;
    default:
        m++;
    }
}

	add_rvar_node(h, m, NULL, 0);
}



int var_chk(l_var **h, char *in, char *st, dt_shell *data)
{
	int a, last, last_pid;

	last = _strlen(st);
	last_pid = _strlen(data->pid);

	int a = 0;
while (in[a]) {
    if (in[a] == '$') {
        switch (in[a + 1]) {
        case '?':
            add_rvar_node(h, 2, st, last);
            i++;
            break;
        case '$':
            add_rvar_node(h, 2, data->pid, last_pid);
            a++;
            break;
        case '\n':
        case '\0':
        case ' ':
        case '\t':
        case ';':
            add_rvar_node(h, 0, NULL, 0);
            break;
        default:
            env_chk(h, in + a, data);
        }
    }
    a++;
}

	return (a);
}


char *input_rep(l_var **head, char *in, char *new_input, int nlen)
{
	l_var *index;
	int a, m, n;

	index = *head;
	int m = 0;
int a = 0;
while (a < nlen) {
    if (input[m] == '$') {
        if (!(index->len_var) && !(index->len_val)) {
            new_input[a] = input[m];
            m++;
        } else if (index->len_var && !(index->len_val)) {
            for (int n = 0; n < index->len_var; n++)
                m++;
            a--;
        } else {
            for (int n = 0; n < index->len_val; n++) {
                new_input[a] = index->val[n];
                a++;
            }
            m += (index->len_var);
            a--;
        }
        index = index->next;
    } else {
        new_input[a] = input[m];
        m++;
    }
    a++;
}

	return (new_input);
}


char *var_rep(char *input, dt_shell *sh_data)
{
	l_var *head, *index;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(sh_data->status);
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
	free_rvar_list(&head);

	return (new_input);
}
