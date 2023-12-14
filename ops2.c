#include "monty.h"

/**
 * sub - Subtracts the top element of the stack from
 * the second top element of the stack
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void sub(stack_t **stack, unsigned int line_number)
{
	int s = 0;

	if (*stack && (*stack)->next)
	{
		s = ((*stack)->next->n) - ((*stack)->n);
		pop(stack, line_number);
		(*stack)->n = s;
	}
	else
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		if (*stack)
			free_dlistint(*stack);
		free(buf);
		exit(EXIT_FAILURE);
	}
}
/**
 * my_div - Divides the second top element of the stack by
 * the top element of the stack
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void my_div(stack_t **stack, unsigned int line_number)
{
	int r = 0;

	if (*stack && (*stack)->next)
	{
		if (((*stack)->n) == 0)
		{
			fprintf(stderr, "L%u: division by zero\n", line_number);
			exit(EXIT_FAILURE);
		}
		r = ((*stack)->next->n) / ((*stack)->n);
		pop(stack, line_number);
		(*stack)->n = r;
	}
	else
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		if (*stack)
			free_dlistint(*stack);
		free(buf);
		exit(EXIT_FAILURE);
	}
}
/**
 * mul - Multiplies the second top element of
 * the stack with the top element of the stack
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void mul(stack_t **stack, unsigned int line_number)
{
	int r = 0;

	if (*stack && (*stack)->next)
	{
		r = ((*stack)->next->n) * ((*stack)->n);
		pop(stack, line_number);
		(*stack)->n = r;
	}
	else
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		if (*stack)
			free_dlistint(*stack);
		free(buf);
		exit(EXIT_FAILURE);
	}
}
/**
 * mod - Computes the rest of the division of the second
 * top element of the stack by the top element of the stack.
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void mod(stack_t **stack, unsigned int line_number)
{
	int r = 0;

	if (*stack && (*stack)->next)
	{
		if (((*stack)->n) == 0)
		{
			fprintf(stderr, "L%u: division by zero\n", line_number);
			exit(EXIT_FAILURE);
		}
		r = ((*stack)->next->n) % ((*stack)->n);
		pop(stack, line_number);
		(*stack)->n = r;
	}
	else
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		if (*stack)
			free_dlistint(*stack);
		free(buf);
		exit(EXIT_FAILURE);
	}
}
/**
 * pchar - Prints the char at the top of the stack, followed by a new line
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void pchar(stack_t **stack, unsigned int line_number)
{
	int av;

	if (*stack)
	{
		av = (*stack)->n;
		if (av >= 0 && av < 128)
			printf("%c\n", av);
		else
		{
			fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
			if (*stack)
				free_dlistint(*stack);
			free(buf);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		free(buf);
		exit(EXIT_FAILURE);
	}
}
