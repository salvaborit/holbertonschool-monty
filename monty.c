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
	char line[1023], lineAux[1023], *delims = " \t\n";
	char *opcode = NULL, *strArg = NULL;
	int lineNum = 1, intArg = 0;


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
		if(opcode)
			strArg = strtok(NULL, delims);

		//printf("opcode = %s\nstrArg = %s\n", opcode, strArg)

		// printf("isdigit_s result = %d\n", isdigit_s(strArg));

		// if(!isdigit_s(strArg) || !strArg || strlen(strArg) != 1)
		// {
		// 	fprintf(stderr, "L%d: usage: push integer\n", lineNum);
		// 	exit (EXIT_FAILURE);
		// }
		if (strArg)
		{
			intArg = atoi(strArg);
			ARG = intArg;
		}

		if (opcode) /* skip blank like */
		{
			f = get_opcode_func(opcode);
			if (f)
				f(&head, lineNum);
			else
			{
				printf("L%d: unknown instruction %s\n", lineNum, opcode);
				exit(EXIT_FAILURE);
			}
		}
		opcode = strArg = NULL;
		intArg = 0;
		lineNum++;
	}

	fclose(fp);
	return(1);
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
	(void) line_number;

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
/**
 * isdigit_s - checks if a string has no digits
 * @s: str to be checked
 * Return: 1 if !decimal, 0 if decimal
 */
int isdigit_s(char *s)
{
	int i;
	char dec = 48; /*ascii 0*/

	while (dec < 58) /*ascii 9 ++*/
	{
		while (s)
		{
			if (s[i] == dec)
				return (1);
			i++;
		}
		dec++;
	}
	return (0);
}