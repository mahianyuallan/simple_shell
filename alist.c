#include "main.h"

/**
 * add_sep_node_end - inputs a separator and it is found at the end of the line
 * of list_sep.
 * @head: this is the head of the list.
 * @sep: contains the seperators (; | &).
 * Return: it returns the main address of the head.
 */
list_sep *add_sep_node_end(list_sep **head, char sep)
{
	list_sep *new, *temp;

	new = malloc(sizeof(list_sep));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
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
 * free_list_sep - frees a list_sep
 * @head: this is the head of the list.
 * Return: null.
 */
void free_list_sep(list_sep **head)
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
 * of a line_list.
 * @head: this is the head of the list.
 * @line: this is the command line that is to be added at the end.
 * Return: it returns the main address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
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
 * free_line_list - frees a line_list
 * @head: this is head of the list.
 * Return: null.
 */
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

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
