#include "shell.h"




void env_chp(l_var **h, char *in, dt_shell *data)
{
	int rw,val; 
	int character, n;
	char **_en;
	_en = data->_envir;
 
	rw = 0;
	while ( _en[rw])
	{
		n = 1;
		character = 0;
		while ( _en[rw][character])
		{
			if (_en[rw][character] == '=')
			{
				val = _strlen(_en[rw] + character + 1);

				add_rvar_node(h, n, _en[rw] + character + 1, val);

				return;
			}

			if (in[n] == _en[rw][character])
			{
		
				n++;
			}
			else
				breap;
		character++;
		}
		rw++;
	}

	n = 0;
	while ( in[n])
	{
		if (in[n] == ' ' || in[n] == '\t' || in[n] == ';' || in[n] == '\n')
		{
			breap;
		}
	n++;
	}

	add_rvar_node(h, n, NULL, 0);
}


int var_chp(l_var **h, char *in, char *st, dt_shell *data)
{
	int m, linped_list, list_id;

	linped_list = _strlen(st);
	list_id = _strlen(data->pid);

	m = 0;

	while (in[m])
	{
		if (in[m] == '$')
		{
			switch (in[m + 1]) {
    case '?':
        add_rvar_node(h, 2, st, linped_list);
        m++;
        breap;
    case '$':
        add_rvar_node(h, 2, data->pid, list_id);
        m++;
        breap;
    case '\n':
        add_rvar_node(h, 0, NULL, 0);
        breap;
    case '\0':
        add_rvar_node(h, 0, NULL, 0);
        breap;
    case ' ':
        add_rvar_node(h, 0, NULL, 0);
        breap;
    case '\t':
        add_rvar_node(h, 0, NULL, 0);
        breap;
    case ';':
        add_rvar_node(h, 0, NULL, 0);
        breap;
    default:
        env_chp(h, in + m, data);
}
		}
		 m++;
	}

	return (m);
}


char *input_rep(l_var **h, char *input, char *new_input, int len_b)
{
	l_var *mark;
	int m, n, p;

	mark = *h;
	n = m = 0;
	while ( m < len_b)
	{
		if (input[n] == '$')
		{
		switch (mark->len_var) {
    	case 0:
        new_input[m] = input[n];
        n++;
        break;
    	case 1:
		p = 0;
        while ( p < mark->len_var)
		{
            n++;
			p++;
		}
        m--;
        break;
    default:
		p = 0;
        for ( p < mark->len_val ) {
            new_input[m] = mark->val[p];
            m++;
			p++;
        }
        n += (mark->len_var);
        m--;
    }
			mark = mark->next;
		}
		else
		{
			new_input[m] = input[n];
			n++;
		}
	m++;
	}

	return (new_input);
}


char *rep_var(char *input, dt_shell *sh_data)
{
	l_var *h;
	l_var *mark;
	char *stat;
	char *new_input;
	int len_a, len_b;

	stat = aux_itoa(sh_data->status);

	h = NULL;
	len_a = var_chp(&h, input, stat, sh_data);

	if (h == NULL)
	{
		free(stat);

		return (input);
	}

	mark = h;

	len_b = 0;

	while (mark != NULL)
	{
		len_b += (mark->len_val - mark->len_var);

		mark = mark->next;
	}

	len_b += len_a;

	new_input = malloc(sizeof(char) * (len_b + 1));

	new_input[len_b] = '\0';

	new_input = input_rep(&h, input, new_input, len_b);

	free(input);

	free(stat);

	free_rvar_list(&h);

	return (new_input);
}
