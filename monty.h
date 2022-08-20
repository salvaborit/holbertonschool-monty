#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

extern int ARG;
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
     int n;
	struct stack_s *prev;
     struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
     char *opcode;
     void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


void execution(FILE *fp, stack_t *head);

/* opcode_funcs1.c */
void (*get_opc_func(char *opcode))(stack_t **stack, unsigned int line_number);
void op_push(stack_t **stack, unsigned int line_number);
void op_pall(stack_t **stack, unsigned int line_number);
void op_pint(stack_t **stack, unsigned int line_number);
void op_pop(stack_t **stack, unsigned int line_number);
/* opcode_funcs2.c */
void op_swap(stack_t **stack, unsigned int line_number);
void op_add(stack_t **stack, unsigned int line_number);
void op_nop(stack_t **stack, unsigned int line_number);

/* list_funcs1.c */
stack_t *add_nodeint(stack_t **head, const int n);
size_t print_dlistint(const stack_t *h);
int delete_dnodeint_at_index(stack_t **head, unsigned int index);
size_t stack_t_len(const stack_t *h);
void free_stack_t(stack_t *head);

/* list_funcs2.c */
int sum_stack_t(stack_t *head);

/* aux_funcs.c */
void monty_ac_verif(int ac);
FILE *fopen_file(char *file);
int isdigit_s(char *s);

#endif /* MONTY_H */
