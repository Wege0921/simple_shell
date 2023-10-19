#include "shell.h"

/**
 * _eputs - Print a string to the standard error stream.
 * @str: The string to be printed.
 *
 * Return: No return value.
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - Write a character to the standard error stream.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	/* If the character is BUF_FLUSH or buffer is full, flush the buffer */
	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}

	/* If the character is not BUF_FLUSH, store it in the buffer */
	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}

/**
 * _putfd - Write a character to the specified file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	/*
	 * If the character is BUF_FLUSH or buffer is full, flush the buffer
	 * to the specified file descriptor
	 */
	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}

	/* If the character is not BUF_FLUSH, store it in the buffer */
	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}

/**
 * _putsfd - Print a string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int _putsfd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		char_count += _putfd(*str++, fd);
	}

	return (char_count);
}

