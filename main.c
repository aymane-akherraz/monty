#include "monty.h"
void exe_ops(FILE *fp);
void free_mem(stack_t *stack);
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
	unsigned int lnum = 1, i;
	instruction_t ops[] = {
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{NULL, NULL}
	};

	while (getline(&buf, &len, fp) > 0)
	{
		t = strtok(buf, " \t\n");
		if (t)
		{
			if (strcmp(t, "push") == 0)
			{
				t = strtok(NULL, " \t");
				if (t == NULL || (!(isdigit(*t)) && t[0] != '-'))
				{
					fprintf(stderr, "L%u: usage: push integer\n", lnum);
					free_mem(stack);
					exit(EXIT_FAILURE);
				}
				else
					push(&stack, atoi(t));
			}
			else if (strcmp(t, "pall") == 0)
			{
				if (stack)
					print_dlistint(stack);
			}
			else
			{
				for (i = 0; ops[i].opcode != NULL; i++)
				{
					if (strcmp(ops[i].opcode, t) == 0)
					{

						ops[i].f(&stack, lnum);
						break;
					}
					else if (ops[i + 1].opcode == NULL && strcmp(t, "nop"))
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
