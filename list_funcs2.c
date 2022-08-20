#include "monty.h"


/**
* sum_stack_t - retutrns the sum of the first 2 nodes of a stack_t list
* @head: pointer to head node
* Return: sum of the first 2 nodes of a stack_t list
*/
int sum_stack_t(stack_t *head)
{
	int sum = 0;

	sum += head->n;
	head = head->next;
	sum += head->n;
	head = head->prev;

	return (sum);
}
