#include "shell.h"






char *char_swp(char *in, int bool)
{
	int m;

	if (bool == 0)
	{
		m = 0;

		while ( in[m])
		{
			if (in[m] == '|')
			{
				if (in[m + 1] != '|')
				{
					in[m] = 16;
				}
				else
				{
					m++;
			    }
			}

			if (in[m] == '&')
			{
				if (in[m + 1] != '&')
				{
					in[m] = 12;
				}
				else
				{
					m++;
				}
			}
			m++;
		}
	}
	else
	{
		m = 0;
		while (in[m])
		{
			in[m] = (in[m] == 16 ? '|' : in[m]);
			in[m] = (in[m] == 12 ? '&' : in[m]);
			m++;
		}
	}
	return (in);
}


void new_nodes(list_sep **head_s, list_line **head_l, char *in)
{
	int m;
	char *strip;

	in = char_swp(in, 0);

	m = 0;
	while (in[m])
	{
		if (in[m] == ';')
		{
			add_sep_node_end(head_s, in[m]);
		}

		if (in[m] == '|' || in[m] == '&')
		{
			add_sep_node_end(head_s, in[m]);
			m++;
		}
		m++;
	}

	strip = _strtok(in, ";|&");
	while (strip != NULL)
	{
		strip = char_swp(strip, 1);
		add_line_node_end(head_l, strip);
		strip = _strtok(NULL, ";|&");
	} 

}


void forward(list_sep **list_s, list_line **list_l, dt_shell *sh_data)
{
	int loop_sep;
	list_sep *ls_s;
	list_line *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (sh_data->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}


int cmd_split(dt_shell *sh_data, char *in)
{

	list_sep *head_s, *list_s;
	list_line *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	new_nodes(&head_s, &head_l, in);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		sh_data->in = list_l->line;
		sh_data->args = line_split(sh_data->in);
		loop = line_ex(sh_data);
		free(sh_data->args);

		if (loop == 0)
			break;

		forward(&list_s, &list_l, sh_data);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_list_sep(&head_s);
	free_list_line(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}


char **line_split(char *in)
{
	size_t size_bit; 
	char *tkn;
	size_t m;
	char **tkns;

	size_bit = BUFF_TOK;
	tkns = malloc(sizeof(char *) * (size_bit));
	if (tkns == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	tkn = _strtok(in, TOK_DELIM);
	tkns[0] = tkn;

	for (m = 1; tkn != NULL; m++)
	{
		if (m == size_bit)
		{
			size_bit += BUFF_TOK;
			tkns = _reallocdp(tkns, m, sizeof(char *) * size_bit);
			if (tkns == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tkn = _strtok(NULL, TOK_DELIM);
		tkns[m] = tkn;
	}

	return (tkns);
}
