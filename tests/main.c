#include "monty.h"
#include <ctype.h>

void usageMsg(void);
void fileMsg(char *);
void op_file(FILE *);
void get_op_func(char *, int, stack_t **);
void push(stack_t **, unsigned int );
void pall(stack_t **, unsigned int);
void mallocError(void);
void unknownError(unsigned int, char *);
void free_stack(stack_t *);
void free_stack_dp(stack_t **);

int main(int ac, char **av)
{
	//printf("entra en el main\n");
	int ret_val = 0;
	FILE *fp;

	if (ac != 2)
	{
		usageMsg();
	}
	
	fp = fopen(av[1], "r");
	if (!fp)
		fileMsg(av[1]);
	//printf("el archivo existe\n");
	op_file(fp);
	return (0);
}

void op_file(FILE *file)
{
	int ret_val = 0;
	stack_t *st = NULL;
	char *buff = NULL;
	char *args = NULL;
	unsigned int line;

	buff = malloc(sizeof(char *) * 1024);
	line = 1;
	while (fgets(buff, 1024, file) != NULL)
	{
			args = strtok(buff, " \n\t");
			if (!args || strcmp(buff, "\n") == 0)
			{
				line++;
				continue;
			}
			int_value.integer = strtok(NULL, " \n\t");
			get_op_func(args, line, &st);
			line++;
	}
	fclose(file);
	free(buff);
	//free_stack(st);
}

void get_op_func(char *args, int line, stack_t **stack)
{
	int i = 0, ret_val = 0, found = 0;
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		/*{"pint", op_pint},
		{"pop", op_pop},
		{"swap", op_swap},
		{"add", op_add},
		{"nop", op_nop},*/
		{NULL, NULL}
	};
	//printf("entra en getopfunc\n");
	while (ops[i].opcode)
	{
		if (strcmp(args, ops[i].opcode) == 0)
		{
			ops[i].f(stack, line);
			found = 1;
		}
		i++;
	}
	if (found != 1)
	{
		unknownError(line, args);
	}
}

void unknownError(unsigned int line, char *args)
{
	fprintf(stderr, "L%d: unknown instruction %s\n", line, args);
	exit(EXIT_FAILURE);
}

void free_stack(stack_t *stack)
{
	stack_t *p;

	while (stack)
	{
		p = stack->next;
		//free(stack);
		stack = p;
	}
}

void free_stack_dp(stack_t **stack)
{
	stack_t *p;

	while (stack)
	{
		p = (*stack)->next;
		//free(stack);
		*stack = p;
	}
}

void push(stack_t **stack, unsigned int line)
{
	stack_t *newNode = NULL;
	char *converted_value = int_value.integer;
	int i = 0;

	//printf("entra en la funcion push\n");
	while(converted_value[i] != '\0')
	{
		//printf("entra en el while de isdigit\n");
		if (isdigit(converted_value[i]) == 0)
		{
			fprintf(stderr, "L%d: usage: push integer\n", line);
			//free_stack_dp(stack);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	//printf("es un entero\n");

	newNode = malloc(sizeof(stack_t));
	if (!newNode)
	{
		mallocError();
	}
	newNode->n = atoi(converted_value);
	newNode->prev = NULL;
	newNode->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = newNode;
	*stack = newNode;
	//printf("crea el nuevo nodo bien\n");
}

void mallocError(void)
{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
}

void pall(stack_t **stack, unsigned int line)
{
	while (*stack)
	{
		printf("%d\n", (*stack)->n);
		*stack = (*stack)->next;
	}
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
