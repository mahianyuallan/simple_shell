#include "main.h"

/**
 * add_rvar_node - the function adds a variable
 * of a l_var list.
 * @head: this is the head of the list.
 * @lvar: this is length of the variable (number of characters).
 * @val: this is value of the given variable.
 * @lval: this is length of the value.
 * Return: this is the main address of the head.
 */
l_var *add_rvar_node(l_var **head, int lvar, char *val, int lval)
{
	l_var *new, *temp;

	new = malloc(sizeof(l_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

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
 * free_rvar_list - frees a l_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_rvar_list(l_var **head)
{
	l_var *temp;
	l_var *curr;

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
