#include "monty.h"
#include <ctype.h>

void op_file(FILE *);
void get_op_func(char *, int, stack_t **);
void push(stack_t **, unsigned int );
void pall(stack_t **, unsigned int);
void free_stack(stack_t **);
void free_stack_dp(stack_t **);
void pint(stack_t **, unsigned int);

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
	op_file(fp);
	return (0);
}

void op_file(FILE *file)
{
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
	free(buff);
	free_stack(&st);
	free(int_value.integer);
	fclose(file);
	return;
}

void get_op_func(char *args, int line, stack_t **stack)
{
	int i = 0;
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		/*{"pop", op_pop},
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
			return;
		}
		i++;
	}
	unknownError(line, args);
}

void pint(stack_t **stack, unsigned int line)
{
	if (!stack || !*stack)
		pintError(line);
	printf("%d\n", (*stack)->n);
}

void free_stack(stack_t **stack)
{
	stack_t *p;

	if (!stack || !*stack)
		return;
	while (*stack)
	{
		p = *stack;
		*stack = p->next;
		free(p);
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
}

void pall(stack_t **stack, unsigned int line)
{
	while (*stack)
	{
		printf("%d\n", (*stack)->n);
		*stack = (*stack)->next;
	}
}


