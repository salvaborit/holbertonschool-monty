#include "monty.h"

/**
 * get_opcode_func - selects the function to perform the opcode
 * @opcode: opcode
 * Return: function linked to opcode to be performed
 */
void (*get_opcode_func(char *opcode))(stack_t **stack, unsigned int line_number)
{
	int i;
	instruction_t opcodes[] = {
		{"push", op_push},
		{"pall", op_pall},
        {"pint", op_pint},
		{NULL, NULL}
	};

	for (i = 0; opcodes[i].opcode; i++)
		if (strcmp(opcodes[i].opcode, opcode) == 0)
			return (opcodes[i].f);
	return (NULL);
}

/**
 * op_push - pushes an int to the top of the stack
 * @stack: pointer to head node of stack_t list
 * @line_number: number of line the opcode was called
 */
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
	ARG = 0;
}

/**
 * op_pall - prints the whole stack starting from the top
 * @stack: pointer to head node of stack_t list
 * @line_number: number of line the opcode was called
 */
void op_pall(stack_t **stack, unsigned int line_number)
{
	(void) line_number;

	print_dlistint(*stack);
}

/**
 * op_pint - prints element at the top of the stack
 * @stack: pointer to head node of stack_t list
 * @line_number: number of line the opcode was called
 */
void op_pint(stack_t **stack, unsigned int line_number)
{
    (void) line_number;
    stack_t *firstNode = *stack;

    printf("%d\n", firstNode->n);
}