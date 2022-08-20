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
	FILE *fp = NULL;
	/*execution*/
	int lineNum = 1;
	char line[1023], lineAux[1023], *opcode = NULL;
	void (*f)(stack_t **stack, unsigned int line_number);

	monty_ac_verif(ac);
	fp = fopen(av[1], "r");
	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	/* execution(fp, head); */
	while (fgets(line, 1024, fp) != NULL)
	{
		strcpy(lineAux, line);
		opcode = strtok(lineAux, " \t\n\r");
		if (opcode) /* skip blank line */
		{
			f = get_opc_func(opcode);
			if (f)
				f(&head, lineNum);
			else
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", lineNum, opcode);
				if (head)
					free_stack_t(head);
				exit(EXIT_FAILURE);
			}
		}
		opcode = NULL;
		lineNum++;
	}
	free_stack_t(head);
	fclose(fp);
	exit(EXIT_SUCCESS);
}

/**
 * execution - main loop
 * @fp: file pointer to .m file to read
 * @head: pointer to head node of stack_t
 */
void execution(FILE *fp, stack_t *head)
{
	int lineNum = 1;
	char line[1023], lineAux[1023], *opcode = NULL;
	void (*f)(stack_t **stack, unsigned int line_number);

	while (fgets(line, 1024, fp) != NULL)
	{
		strcpy(lineAux, line);
		opcode = strtok(lineAux, " \t\n\r");

		if (opcode) /* skip blank line */
		{
			f = get_opc_func(opcode);
			if (f)
				f(&head, lineNum);
			else
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", lineNum, opcode);
				if (head)
					free_stack_t(head);
				exit(EXIT_FAILURE);
			}
		}
		opcode = NULL;
		lineNum++;
	}
}
