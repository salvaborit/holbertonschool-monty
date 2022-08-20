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

/**
* delete_dnodeint_at_index - deletes node at index of a dlistint_t list
* @head: pointer to head node
* @index: index of node to delete
* Return: 1 if success, -1 if failure
*/
int delete_dnodeint_at_index(stack_t **head, unsigned int index)
{
	stack_t *temp, *prevNode, *nextNode, *bruh;
	unsigned int i;

	temp = *head;
	if (!temp)
		return (-1);
	if (index == 0)
	{
		*head = (*head)->next;
		(*head)->prev = NULL;
		free(temp);
		return (1);
	}
	for (i = 0; i < index; i++)
	{
		temp = temp->next;
		if (!temp)
			return (-1);
	}
	if (!temp->next)
	{
		bruh = temp;
		bruh = temp->prev;
		bruh->next = NULL;
		free(temp);
		return (1);
	}
	prevNode = temp->prev;
	nextNode = temp->next;
	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	free(temp);
	return (1);
}

/**
* free_stack_t - frees a stack_t list
* @head: pointer to head node
*/
void free_stack_t(stack_t *head)
{
	stack_t *temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}