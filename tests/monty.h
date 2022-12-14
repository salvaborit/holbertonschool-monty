#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

extern char *global;
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

/**
 * opc_int - global variable for the second parameter in the lines
 * @integer: the parameter
 * Description: This global variable stores the value of the 
 * second parameter in each itearion of the while loop in 
 * the "op_file" function (see main.c for more details)
 */
/*typedef struct opc_int
{
        char *integer;
} opc_i;
opc_i int_value;*/

void usageMsg(void);
void fileMsg(char *);
void mallocError(void);
void unknownError(unsigned int, char *);
void pintError(unsigned int);

#endif /*MONTY_H*/