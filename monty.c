#include "monty.h"
int ARG = 0;

/**
 * main - monty bitcode interpreter main execution
 * @ac: number of args passed to command line
 * @av: array containing args passed to command line
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int ac, char *av[])
{
	stack_t *head = NULL;
	void (*f)(stack_t **stack, unsigned int line_number);
	FILE *fp = NULL;
	char line[1023], lineAux[1023], *delims = " \t\n\r";
	char *opcode = NULL, *strArg = NULL;
	int lineNum = 1;


	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	fp = fopen(av[1], "r");
	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, 1024, fp) != NULL)
	{
		strcpy(lineAux, line);
		opcode = strtok(lineAux, delims);

		if (opcode) /* skip blank line */
		{
			f = get_opc_func(opcode);
			if (f)
				f(&head, lineNum);
			else
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", lineNum, opcode);
				exit(EXIT_FAILURE);
			}
		}
		opcode = strArg = NULL;
		lineNum++;
	}
	free_stack_t(head);
	fclose(fp);
	exit(EXIT_SUCCESS);
}
