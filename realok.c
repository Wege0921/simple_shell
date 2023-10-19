#include "shell.h"

/**
 * _memset - Fill memory with a constant byte.
 * @s: Pointer to the memory area to be filled.
 * @b: The byte value to fill 's' with.
 * @n: The number of bytes to be filled.
 *
 * Return: 's', a pointer to the filled memory area.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		s[index] = b;

	return (s);
}



/**
 * ffree - Frees a string array.
 * @str_array: The array of strings to be freed.
 */
void ffree(char **str_array)
{
	char **ptr = str_array;

	if (!str_array)
		return;

	while (*str_array)
		free(*str_array++);

	free(ptr);
}


/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ed block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated block or NULL on failure.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (new_ptr);
}

