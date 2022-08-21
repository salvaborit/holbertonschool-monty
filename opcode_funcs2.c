#include "monty.h"

/**
 * op_swap - swaps the top two elements of the stack
 * @stack: pointer to head node of stack_t list
 * @line_number: number of line the opcode was called
 */
void op_swap(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	stack_t *head = *stack;
	int sum, i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	/*stackSize = stack_t_len(head);*/
	/*if (stackSize < 2)*/
	if (i < 2)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	sum = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = sum;
}

/**
 * op_add - adds the top two elements of the stack
 * @stack: pointer to head node of stack_t list
 * @line_number: number of line the opcode was called
 */
void op_add(stack_t **stack, unsigned int line_number)
{
	stack_t *head = *stack;
	int /*stackSize = 0,*/ sum, i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	/*stackSize = stack_t_len(head);*/
	/*if (stackSize < 2)*/
	if (i < 2)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	head = (*stack)->next;
	sum = (*stack)->n + head->n;
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
	return;
}
