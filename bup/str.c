#include "shell.h"

/**
 * _strlen - Calculate the length of a string.
 * @s: The string to measure.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;
	return (length);
}


/**
 * _strcmp - Compare two strings lexicographically.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, or zero if s1 equals s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


/**
 * starts_with - Check if a string starts with a specific substring.
 * @haystack: The string to search within.
 * @needle: The substring to find.
 *
 * Return: A pointer to the character
 *	following the matching substring or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle != *haystack)
			return (NULL);
		needle++;
		haystack++;
	}
	return ((char *)haystack);
}

/**
 * _strcat - Concatenate two strings.
 * @dest: The destination buffer to which @src is appended.
 * @src: The source buffer containing the string to append.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *result = dest;/* Store the original destination pointer */

	while (*dest)
		dest++;/* Move to the end of the destination string */

	while (*src)
		*dest++ = *src++;/* Append characters */

	*dest = *src;  /* Ensure the null terminator is copied at the end */
	return (result);  /* Return a pointer to the concatenated string */
}

