#include "monty.h"

void errorMsg(char *);
void op_file(char *);

int main(int ac, char **av)
{
	if (ac != 2)
	{
		errorMsg("USAGE: monty file\n");
	}
	op_file(av[1]);
	return (0);
}

void op_file(char *file)
{
	char *buff;
	char *tok = NULL;
	char **tokens;
	FILE *fp = fopen(file, "r");
	int i = 0, j;

	buff = malloc(1024);
	tokens = malloc(sizeof(char *) * 1024);
	while (fgets(buff, 1024, fp))
	{
		tok = strtok(buff, " \t\n");
		while (tok != NULL)
		{
			tokens[i] = tok;
			//printf("%s\n", tok);
			tok = strtok(NULL, " \t\n");
			i++;
		}
	}
	fclose(fp);
	tokens[i] = NULL;
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}

void errorMsg(char *message)
{
	printf("%s", message);
	exit(EXIT_FAILURE);
}
