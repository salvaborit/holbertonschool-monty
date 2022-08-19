#include "monty.h"
#include <ctype.h>

void get_op_func(char *, int, stack_t **);
void push(stack_t **, unsigned int );
void pall(stack_t **, unsigned int);
void free_stack(stack_t **);
void pint(stack_t **, unsigned int);
void pop(stack_t **, unsigned int);
char *global = NULL;

int main(int ac, char **av)
{
	stack_t *st = NULL;
	char *buff = NULL;
	char *args = NULL;
	unsigned int line;
	FILE *fp;

	if (ac != 2)
	{
		usageMsg();
	}
	
	fp = fopen(av[1], "r");
	if (!fp)
		fileMsg(av[1]);
	buff = malloc(sizeof(char *) * 1024);
	line = 1;
	while (fgets(buff, 1024, fp) != NULL)
	{
			args = strtok(buff, " \n\t");
			if (!args || strcmp(buff, "\n") == 0)
			{
				line++;
				continue;
			}
			global = strtok(NULL, " \n\t");
			get_op_func(args, line, &st);
			line++;
	}
	free(buff);
	//free_stack(&st);
	fclose(fp);
	return (0);
}

void get_op_func(char *args, int line, stack_t **stack)
{
	int i = 0, found = 0;
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		/*{"swap", op_swap},
		{"add", op_add},
		{"nop", op_nop},*/
		{NULL, NULL}
	};

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

void pop(stack_t **stack, unsigned int line)
{
	stack_t *p = *stack;

	if (!p)
	{
		//popError(line);
	}
	*stack = (*stack)->next;
	free(p);
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
		*stack = (*stack)->next;
		free(p);
	}
}

void push(stack_t **stack, unsigned int line)
{
	stack_t *newNode = NULL;
	char *converted_value = global;
	int i = 0;

	while(converted_value[i] != '\0')
	{
		if (isdigit(converted_value[i]) == 0)
		{
			fprintf(stderr, "L%d: usage: push integer\n", line);
			exit(EXIT_FAILURE);
		}
		i++;
	}

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
