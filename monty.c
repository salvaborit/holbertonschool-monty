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

		if (opcode) /* skip blank like */
		{
			f = get_opcode_func(opcode);
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

	fclose(fp);
	return(1);
}

/**
 * isdigit_s - checks if a string is only made up of digits (no negative)
 * @s: str to be checked
 * Return: 1 if all are digits, 0 if at least 1 is not a digit
 */
int isdigit_s(char *s)
{
	int i = 1;

	if (!s)
		return (0);
	if ((s[0] < '0' || s[0] > '9') && s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void (*get_opcode_func(char *opcode))(stack_t **stack, unsigned int line_number)
{
	int i;
	instruction_t opcodes[] = {
		{"push", op_push},
		{"pall", op_pall},
		{NULL, NULL}
	};

	for (i = 0; opcodes[i].opcode; i++)
		if (strcmp(opcodes[i].opcode, opcode) == 0)
			return (opcodes[i].f);
	return (NULL);
}

void op_push(stack_t **stack, unsigned int line_number)
{
	char *strArg = NULL;

	strArg = strtok(NULL, " \t\n\r");

	if (!strArg || isdigit_s(strArg) == 0)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	ARG = atoi(strArg);
	add_nodeint(stack, ARG);
}

void op_pall(stack_t **stack, unsigned int line_number)
{
	(void) line_number;

	print_dlistint(*stack);
}

/**
* add_nodeint - adds a new node at the beginning of a stack_t list
* @head: pointer to first node
* @n: int to put in new node
* Return: address of new element or NULL if failed
*/
stack_t *add_nodeint(stack_t **head, const int n)
{
	stack_t *newNode;

	newNode = malloc(sizeof(stack_t));
	if (newNode == NULL)
		return (NULL);

	newNode->n = n;
	newNode->next = *head;
	*head = newNode;
	return (newNode);
}

/**
 * print_dlistint - prints all the elements of a dlistint_t list
 * @h: pointer to head node
 * Return: number of nodes
 */
size_t print_dlistint(const stack_t *h)
{
	int stackSize = 0;

	while (h)
	{
		printf("%d\n", h->n);
		h = h->next;
		stackSize++;
	}
	return (stackSize);
}