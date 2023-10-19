#include "shell.h"

/**
 * _strcpy - Copy a string from source to destination.
 * @dest: The destination buffer to which the string is copied.
 * @src: The source buffer containing the string to be copied.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
	int index = 0;

	/* Handle edge cases and check for source and destination equality */
	if (dest == src || src == NULL)
		return (dest);

	while (src[index])
	{
		dest[index] = src[index];
		/* Copy character from source to destination */
		index++;
	}
	dest[index] = '\0';/* Ensure null-termination of the destination string */
	return (dest);
}

/**
 * _strdup - Duplicate a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string or NULL if
 *	memory allocation fails.
 */
char *_strdup(const char *str)
{
	int str_length = 0;  /* Length of the input string */
	char *duplicate;     /* Pointer to the duplicated string */

	/* Handle the case where the input string is NULL */
	if (str == NULL)
		return (NULL);

	/* Calculate the length of the input string */
	while (str[str_length])
		str_length++;

	/* Allocate memory for the duplicated string */
	duplicate = malloc(sizeof(char) * (str_length + 1));

	/* Check for memory allocation failure */
	if (duplicate == NULL)
		return (NULL);

	/* Copy characters from the input string to the duplicated string */
	for (str_length++; str_length--;)
		duplicate[str_length] = str[str_length];

	return (duplicate);
}

/**
 * _puts - Print a string to the standard output.
 * @str: The string to be printed.
 *
 * Return: No return value.
 */
void _puts(char *str)
{
	int index = 0;  /* Index to traverse the string */

	/* Check if the input string is NULL */
	if (!str)
		return;

	/* Loop through the string and print each character */
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - Writes a character to the standard output.
 * @c: The character to be printed.
 *
 * Return: On success, returns 1.
 * On error, returns -1 and sets errno appropriately.
 */
int _putchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	/* If the character is a buffer flush or the buffer is full*/
	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}

	/* If the character is not a buffer flush, add it to the buffer */
	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}



