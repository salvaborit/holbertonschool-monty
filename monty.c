#include "monty.h"

/**
 * main - monty bitcode interpreter main execution
 * @ac: number of args passed to command line
 * @av: array containing args passed to command line
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int ac, char *av[])
{
/*	stack_t *head = NULL; */
	FILE *fp = NULL;
	char line[1023], lineAux[1023], *delims = " \t\n";
	char *opcode = NULL, *strArg = NULL;
	int intArg = 0;

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
		strArg = strtok(NULL, delims);
		if (strArg)
			intArg = atoi(strArg);
		printf("opcode = %s, strArg = %s, intArg = %d\n", opcode, strArg, intArg);

		opcode = strArg = NULL;
		intArg = 0;
	}

	fclose(fp);
	return(1);
}
/*
void (*opcode(char *s))()

fprintf(stderr, "Error: malloc failed");
exit(EXIT_FAILURE);
*/