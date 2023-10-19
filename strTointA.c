#include "shell.h"

/**
 * _isalpha - Check if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if 'c' is an alphabetic character, 0 otherwise.
 */
int _isalpha(int c)
{
	int is_alphabetic = 0; /* Initialize result to not an alpha char */

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		is_alphabetic = 1; /* Set to 1 if character is alphabetic */
	}

	return (is_alphabetic);
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer if numbers
 *	are present in the string, 0 otherwise.
 */
int _atoi(char *s)
{
	int index, sign = 1, state = 0, output;
	unsigned int result = 0;

	for (index = 0; s[index] != '\0' && state != 2; index++)
	{
		if (s[index] == '-')
			sign *= -1;

		if (s[index] >= '0' && s[index] <= '9')
		{
			state = 1;
			result *= 10;
			result += (s[index] - '0');
		}
		else if (state == 1)
			state = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

