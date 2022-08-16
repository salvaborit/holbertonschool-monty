#include "monty.h"

/**
 * main - monty bitcode interpreter main execution
 * @ac: argument count
 * @av: arguments to command line
 * Return: 0 on success
 */

int main(int ac, char *av[])
{
	FILE *fp = NULL;
	char *line = NULL, *got = NULL;

	/* if arg count is wrong */
	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	/* if file opening fails */
	fp = fopen(av[1], "r");
	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	do {
		line = malloc(1024);
		if (!line)
			{
				fprintf(stderr, "Error: malloc failed\n");
				exit(EXIT_FAILURE);
			}
		got = fgets(line, 1024, fp);
		printf("%s", line);
	} while (got);

	fclose(fp);
	return(1);
}