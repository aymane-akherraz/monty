#include "monty.h"

/**
 * push - Adds a new node at the top of the stack
 * @stack: A pointer to the top of the stack
 * @n: integer
 *
 * Return: Nothing
*/

void push(stack_t **stack, int n)
{
	stack_t *new;

	new = malloc(sizeof(stack_t));
	if (!new)
	{
		fprintf(stderr, "Error: malloc failed\n");
		if (*stack)
			free_dlistint(*stack);
		free(buf);
		exit(EXIT_FAILURE);
	}

	new->n = n;
	new->prev = NULL;
	new->next = *stack;
	if (*stack)
		(*stack)->prev = new;
	*stack = new;
}
/**
 * pint - Prints the value at the top of the stack, followed by a new line
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack)
		printf("%d\n", (*stack)->n);
	else
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		free(buf);
		exit(EXIT_FAILURE);
	}
}
/**
 * pop - Removes the top element of the stack.
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *ptr;

	if (*stack)
	{
		ptr = (*stack)->next;
		if (ptr)
			ptr->prev = NULL;
		free(*stack);
		*stack = ptr;
	}
	else
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		free(buf);
		exit(EXIT_FAILURE);
	}
}
/**
 * swap - Swaps the top two elements of the stack.
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *ptr;

	if (*stack && (*stack)->next)
	{
		ptr = (*stack)->next;

		(*stack)->next->prev = NULL;
		(*stack)->next = (*stack)->next->next;
		if (ptr->next)
			ptr->next->prev = *stack;
		(*stack)->prev = ptr;
		ptr->next = *stack;
		*stack = ptr;
	}
	else
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		if (*stack)
			free_dlistint(*stack);
		free(buf);
		exit(EXIT_FAILURE);
	}
}
/**
 * add - Adds the top two elements of the stack.
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void add(stack_t **stack, unsigned int line_number)
{
	int s = 0;

	if (*stack && (*stack)->next)
	{
		s = ((*stack)->n) + ((*stack)->next->n);
		pop(stack, line_number);
		(*stack)->n = s;

	}
	else
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		if (*stack)
			free_dlistint(*stack);
		free(buf);
		exit(EXIT_FAILURE);
	}
}
