
#include "shell.h"

/**
 * list_len - Counts the number of nodes in a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Returns: The number of nodes in the list.
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - Converts a linked list of strings to an array of strings.
 * @head: Pointer to the first node of the list.
 *
 * Return: An array of strings (char**).
 */



char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t x = list_len(head), y;
	char **strs;
	char *str;

	if (!head || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * print_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - Returns the node whose string
 *	starts with the given prefix.
 * @node: Pointer to the list head.
 * @prefix: The string to match at the beginning of the node's string.
 * @c: The next character after the prefix to
 *	match (-1 to match any character).
 *
 * Return: The matched node or NULL if no match is found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *match = NULL;

	while (node)
	{
		match = starts_with(node->str, prefix);
		if (match && ((c == -1) || (*match == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 * get_node_index - Get the index of a node within a linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node whose index is to be determined.
 *
 * Return: The index of the node or -1 if the node
 *	is not found in the list.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

