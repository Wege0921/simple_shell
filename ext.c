#include "shell.h"

/**
 * _strncpy - Copy a string up to a specified number of characters
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 * @n: Number of characters to copy
 *
 * Return: Pointer to the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *original_dest = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (original_dest);
}
/**
 * _strncat - Concatenate two strings, limiting the number of bytes used
 * @dest: The first string to which 'src' will be concatenated
 * @src: The second string to be concatenated
 * @n: The maximum number of bytes to be used
 *
 * Return: Pointer to the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int dest_index, src_index;
	char *original_dest = dest;

	dest_index = 0;
	src_index = 0;

	/* Move the 'dest' pointer to the end of the string */
	while (dest[dest_index] != '\0')
		dest_index++;

	/* Concatenate 'src' to 'dest' while respecting the limit 'n' */
	while (src[src_index] != '\0' && src_index < n)
	{
		dest[dest_index] = src[src_index];
		dest_index++;
		src_index++;
	}

	/* Ensure the concatenated string is null-terminated */
	if (src_index < n)
		dest[dest_index] = '\0';

	return (original_dest);
}

/**
 * _strchr - Locate a character in a string
 * @s: The string to be searched
 * @c: The character to find
 *
 * Return: Pointer to the first occurrence of 'c' in 's' or NULL if not found
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}

	return (NULL);
}

