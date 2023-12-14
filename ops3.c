#include "monty.h"

/**
 * pstr - Prints the string starting at the top of the stack,
 * followed by a new line.
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *ptr;
	(void)line_number;

	ptr = *stack;

	while (ptr && (ptr->n > 0 && ptr->n < 128))
	{
		printf("%c", ptr->n);
		ptr = ptr->next;
	}
	printf("\n");
}
/**
 * rotl - Rotates the stack to the top.
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *ptr;
	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;

	ptr = *stack;

	while (ptr->next)
		ptr = ptr->next;

	ptr->next = *stack;
	(*stack)->prev = ptr;
	ptr = (*stack)->next;
	(*stack)->next = NULL;
	*stack = ptr;
}
/**
 * rotr - Rotates the stack to the bottom
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *ptr;
	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;

	ptr = *stack;

	while (ptr->next)
		ptr = ptr->next;

	ptr->prev->next = NULL;
	ptr->prev = NULL;
	ptr->next = *stack;
	(*stack)->prev = ptr;
	*stack = ptr;
}
