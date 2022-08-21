#include "monty.h"

/**
 * op_swap - swaps the top two elements of the stack
 * @stack: pointer to head node of stack_t list
 * @line_number: number of line the opcode was called
 */
void op_swap(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}

/**
 * op_add - adds the top two elements of the stack
 * @stack: pointer to head node of stack_t list
 * @line_number: number of line the opcode was called
 */
void op_add(stack_t **stack, unsigned int line_number)
{
	stack_t *head = *stack;
	int stackSize = 0, sum = 0;

	stackSize = stack_t_len(head);
	if (stackSize < 2)
	{
		fprintf(stderr, "L%d: can't add, stack too short", line_number);
		exit(EXIT_FAILURE);
	}
	sum = (*stack)->n + head->n;
	head = head->next;
	op_pop(stack, line_number);
	head->n = sum;
	/*sum = sum_stack_t(head);
	delete_dnodeint_at_index(&head, 0);
	delete_dnodeint_at_index(&head, 1);
	add_nodeint(&head, sum);*/
}

/**
 * op_nop - does nothing
 * @stack: pointer to head node of stack_t list
 * @line_number: number of line the opcode was called
 */
void op_nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}
