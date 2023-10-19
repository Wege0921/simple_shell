#include "shell.h"

/**
 * print_d - Print a decimal (integer) number (base 10).
 * @input: The input integer.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*put_char)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		put_char = _eputchar;

	if (input < 0)
	{
		abs_value = -input;
		put_char('-');
		count++;
	}
	else
		abs_value = input;

	current = abs_value;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			put_char('0' + current / i);
			count++;
		}
		current %= i;
	}

	put_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Convert a number to a string in the specified base.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags (e.g., lowercase).
 *
 * Return: A string representation of the number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *result;
	unsigned long n = num;
	/* Determine the sign of the number if applicable */
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	/* Choose the character array based on flags (lowercase or uppercase) */
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	result = &buffer[49];
	*result = '\0';

	do {
		*--result = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--result = sign;

	return (result);
}

/**
 * remove_comments - Replace the first instance of '#' with '\0'.
 * @buf: Pointer to the string to modify.
 *
 * Return: Always 0.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		/* If '#' is found and it's either at the beginning or preceded by a space */
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break; /* Stop processing after the first '#' */
		}
	}
}

