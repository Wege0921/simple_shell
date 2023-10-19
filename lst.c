#include "shell.h"

/**
 * add_node - Adds a new node to the start of the list.
 * @head: Address of the pointer to the head node.
 * @str: String to be stored in the node's str field.
 * @num: Index used by history.
 *
 * Return: Address of the newly created node.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}



/**
 * add_node_end - Appends a new node to the end of the list.
 * @head: Address of the pointer to the head node.
 * @str: String to be stored in the node's str field.
 * @num: Index used by history.
 *
 * Return: Address of the newly created node.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *current_node;

	if (!head)
		return (NULL);

	current_node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}
/**
 * print_list_str - Prints the 'str' element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Number of nodes in the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t node_count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		node_count++;
	}

	return (node_count);
}
/**
 * delete_node_at_index - Deletes a node at the specified index.
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current, *previous;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		current = *head;
		*head = (*head)->next;
		free(current->str);
		free(current);
		return (1);
	}

	current = *head;
	while (current)
	{
		if (i == index)
		{
			previous->next = current->next;
			free(current->str);
			free(current);
			return (1);
		}
		i++;
		previous = current;
		current = current->next;
	}

	return (0);
}

/**
 * free_list - Frees all nodes in a linked list.
 * @head: Address of the pointer to the head node.
 *
 * This function deallocates memory for all nodes in the list and sets the
 * head pointer to NULL.
 */
void free_list(list_t **head)
{
	list_t *current, *next, *list_head;

	if (!head || !*head)
		return;

	list_head = *head;
	current = list_head;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*head = NULL;
}



