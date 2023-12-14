#include "monty.h"
/**
 * print_dlistint - prints all the elements of the stack
 * @stack: A pointer to the top of the stack
 *
 * Return: Nothing
*/
void print_dlistint(const stack_t *stack)
{
	while (stack)
	{
		printf("%d\n", stack->n);
		stack = stack->next;
	}
}
/**
 * free_dlistint - Frees the stack
 * @head: A pointer to the top of the stack
 *
 * Return: Nothing
*/
void free_dlistint(stack_t *head)
{
	stack_t *ptr;

	while (head)
	{
		ptr = head->next;
		free(head);
		head = ptr;
	}
}
/**
 * add_dnodeint - Adds a new node at the beginning of a stack_t list
 * @head: A pointer to the head of the list
 * @n: integer
 *
 * Return: Nothing
*/
stack_t *add_dnodeint(stack_t **head, const int n)
{
	stack_t *new;

	new = malloc(sizeof(stack_t));
	if (!new)
	{
		fprintf(stderr, "Error: malloc failed\n");
		if (*head)
			free_dlistint(*head);
		free(buf);
		exit(EXIT_FAILURE);
	}

	new->n = n;
	new->prev = NULL;
	new->next = *head;
	if (*head)
		(*head)->prev = new;
	*head = new;

	return (new);
}
/**
 * add_dnodeint_end - Adds a new node at the end of a stack_t list
 * @head: A pointer to the head of the list
 * @n: integer
 *
 * Return: the address of the new element, or NULL if it failed
*/
stack_t *add_dnodeint_end(stack_t **head, const int n)
{
	stack_t *new, *ptr;

	new = malloc(sizeof(stack_t));
	if (!new)
	{
		fprintf(stderr, "Error: malloc failed\n");
		if (*head)
			free_dlistint(*head);
		free(buf);
		exit(EXIT_FAILURE);
	}

	new->n = n;
	new->next = NULL;
	if (*head)
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;

		new->prev = ptr;
		ptr->next = new;
	}
	else
	{
		new->prev = *head;
		*head = new;
	}
	return (new);
}
