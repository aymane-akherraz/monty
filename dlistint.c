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
