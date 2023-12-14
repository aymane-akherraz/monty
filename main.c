#include "monty.h"
void exe_ops(FILE *fp);
void free_mem(stack_t *stack);
void push_err(stack_t *stack, unsigned int line_number);
char *buf = NULL;

/**
 * main - The entry point of the program
 * @argc: The number of arguments passed
 * @argv: A pointer array which points to each argument passed to the program
 * Return: Always 0
*/
int main(int argc, char *argv[])
{
	FILE *fptr;
	char *fname;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	fname = argv[1];
	fptr = fopen(fname, "r");
	if (fptr == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", fname);
		exit(EXIT_FAILURE);
	}
	exe_ops(fptr);
	fclose(fptr);
	return (0);
}
/**
 * exe_ops - executes available instructions
 * @fp: A pointer to the given file
*/
void exe_ops(FILE *fp)
{
	stack_t *stack = NULL;
	char *t;
	size_t len = 0;
	unsigned int lnum = 1, i, mode = 0;
	instruction_t ops[] = {{"pint", pint}, {"pop", pop}, {"swap", swap},
		{"add", add}, {"sub", sub}, {"div", my_div}, {"mul", mul}, {"mod", mod},
		{"pchar", pchar}, {"pstr", pstr}, {"rotl", rotl}, {"rotr", rotr},
		{NULL, NULL}
	};

	while (getline(&buf, &len, fp) > 0)
	{
		t = strtok(buf, " \t\n");
		if (t)
		{
			if (strcmp(t, "queue") == 0)
				mode = 1;
			else if (strcmp(t, "stack") == 0 && mode)
				mode = 0;
			else if (strcmp(t, "push") == 0)
			{
				t = strtok(NULL, " \t\n");
				if (t == NULL)
					push_err(stack, lnum);
				for (i = 0; t[i] != '\0'; i++)
				{
					if (!isdigit(t[i]) && t[i] != '-')
						push_err(stack, lnum);
				}
				push(&stack, atoi(t), mode);
			}
			else if (strcmp(t, "pall") == 0)
			{
				if (stack)
					print_dlistint(stack);
			}
			else if (*t == '#' || strcmp(t, "nop") == 0)
				;
			else
			{
				for (i = 0; ops[i].opcode != NULL; i++)
				{
					if (strcmp(ops[i].opcode, t) == 0)
					{

						ops[i].f(&stack, lnum);
						break;
					}
					else if (ops[i + 1].opcode == NULL)
					{
						fprintf(stderr, "L%u: unknown instruction %s\n", lnum, t);
						free_mem(stack);
						exit(EXIT_FAILURE);
					}
				}
			}
		}
		lnum++;
		free(buf);
		buf = NULL;
	}
	free_mem(stack);
}
/**
 * free_mem - frees manually preallocated memory using malloc
 * @stack: A pointer to the top of the stack
*/
void free_mem(stack_t *stack)
{
	if (stack)
		free_dlistint(stack);
	if (buf)
		free(buf);
}
/**
 * push_err - Prints an error and exits
 * @stack: A pointer to the top of the stack
 * @line_number: the line number of the given opcode
*/
void push_err(stack_t *stack, unsigned int line_number)
{
	fprintf(stderr, "L%u: usage: push integer\n", line_number);
	free_mem(stack);
	exit(EXIT_FAILURE);
}
