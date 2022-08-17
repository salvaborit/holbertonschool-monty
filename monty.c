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
	char line[1023], lineAux[1023], *delims = " \t\n", *token = NULL;
	char **lineArr = NULL;
	int i;

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
		lineArr = malloc(1024);
		if (!lineArr)
		{
			fprintf(stderr, "Error: malloc failed");
			exit(EXIT_FAILURE);
		}

		strcpy(lineAux, line);
		token = strtok(lineAux, delims);
		for (i = 0; token; i++)
		{
			lineArr[i] = strdup(token);
			token = strtok(NULL, delims);
		}
		lineArr[i] = NULL;

		while (lineArr[i])
			printf("%s ", lineArr[i++]);

		if (lineArr)
			free(lineArr);
		lineArr = NULL;
	}

	fclose(fp);
	return(1);
}
/*
void (*opcode(char *s))()
*/