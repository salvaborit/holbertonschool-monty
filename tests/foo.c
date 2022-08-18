#include "monty.h"

void usageMsg(void);
void fileMsg(char *);
void op_file(FILE *);
void get_op_func(char *, int);

int main(int ac, char **av)
{
	FILE *fp;

	if (ac != 2)
	{
		usageMsg();
	}
	
	fp = fopen(av[1], "r");
	if (!fp)
		fileMsg(av[1]);
	op_file(fp);
	return (0);
}

void op_file(FILE *file)
{
	char *buff = NULL;
	char *args = NULL;
	unsigned int line;

	buff = malloc(sizeof(char * ) * 1024);
	line = 1;
	while (fgets(buff, 1024, file) != NULL)
	{
			args = strtok(buff, " \n\t");
			if (!args || strcmp(buff, "\n") == 0)
			{
				line++;
				continue;
			}
			token.integer = strtok(NULL, " \n\t");
			get_op_func(args, line);
			line++;
	}
	fclose(file);
	free(buff);
}

void get_op_func(char *args, int line)
{
	//printf("llega a la funcion\n");
	printf("Argumento: %s\n", args);
	printf("Entero: %s\n", token.integer);
	printf("En la linea: %d\n", line);
}
void fileMsg(char *file)
{
	
	exit(EXIT_FAILURE);
}

void usageMsg(void)
{
	write(STDERR_FILENO, "USAGE: monty file", 18);
	exit(EXIT_FAILURE);
}