#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @ptr: Pointer to a pointer to be freed.
 *
 * Return: 1 if freed, 0 if not.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

