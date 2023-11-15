#include "shell.h"

/**
 * separ_add_node - inputs a separator and it is found at the end of the line
 * of list_sep.
 * @head: this is the head of the list.
 * @sep: contains the seperators (; | &).
 * Return: it returns the main address of the head.
 */
list_sep *separ_add_node(list_sep **head, char separ);
{
	list_sep *new, *temp;

	new = malloc(sizeof(list_sep));
	if (new == NULL)
		return (NULL);

	new->separator = separ;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * separ_free_list - frees a list_sep
 * @head: this is the head of the list.
 * Return: null.
 */
void separ_free_list(list_sep **head)
{
	list_sep *temp;
	list_sep *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - it adds a command line
 * of a list_line.
 * @head: this is the head of the list.
 * @line: this is the command line that is to be added at the end.
 * Return: it returns the main address of the head.
 */

list_line *line_add_node(list_line **head, char *line);
{
	list_line *new, *temp;

	new = malloc(sizeof(list_line));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_list_line - frees a list_line
 * @head: this is head of the list.
 * Return: null.
 */
void free_list_line(list_line **head)
{
	list_line *temp;
	list_line *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
