#include "monty.h"

void pintError(unsigned int line)
{
	fprintf(stderr, "L%d: can't pint, stack empty\n", line);
	//free_stack(&)
	exit(EXIT_FAILURE);
}

void unknownError(unsigned int line, char *args)
{
	fprintf(stderr, "L%d: unknown instruction %s\n", line, args);
	exit(EXIT_FAILURE);
}

void mallocError(void)
{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
}

void fileMsg(char *file)
{
	fprintf(stderr, "Error: Can't open the file %s\n", file);
	exit(EXIT_FAILURE);
}

void usageMsg(void)
{
	fprintf(stderr, "USAGE: monty file\n");
	exit(EXIT_FAILURE);
}