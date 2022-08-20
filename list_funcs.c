#include "monty.h"

/**
* add_nodeint - adds a new node at the beginning of a stack_t list
* @head: pointer to first node
* @n: int to put in new node
* Return: address of new element or NULL if failed
*/
stack_t *add_nodeint(stack_t **head, const int n)
{
	stack_t *newNode;

	newNode = malloc(sizeof(stack_t));
	if (newNode == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	newNode->n = n;
	newNode->next = *head;
	*head = newNode;
	return (newNode);
}

/**
 * print_dlistint - prints all the elements of a dlistint_t list
 * @h: pointer to head node
 * Return: number of nodes
 */
size_t print_dlistint(const stack_t *h)
{
	int stackSize = 0;

	while (h)
	{
		printf("%d\n", h->n);
		h = h->next;
		stackSize++;
	}
	return (stackSize);
}