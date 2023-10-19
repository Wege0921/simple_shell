#include "shell.h"

/**
 * _erratoi - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number if successful, -1 on error.
 */
int _erratoi(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* Skip leading plus sign if present */

	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');
			if (result > INT_MAX)
				return (-1);  /* Integer overflow */
		}
		else
			return (-1);  /* Non-numeric character found */
	}

	return (result);
}

/**
 * print_error - Print an error message to the standard error stream.
 * @info: Pointer to the parameter and return info structure.
 * @estr: String containing the specified error type.
 *
 * Return: No return value.
 */
void print_error(info_t *info, char *estr)
{
	/* Print the filename, line number, command, and the error message */
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

