#include "shell.h"

/**
 * interactive - Check if the shell is in interactive mode.
 * @info: Pointer to the info_t struct containing shell information
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */

int interactive(info_t *info)
{
	int is_interactive = 0;  /* Initialize the result to non-interactive */

	if (isatty(STDIN_FILENO) && info->readfd <= 2)
	{
		is_interactive = 1; /* Set to 1 if in interactive mode */
	}

	return (is_interactive);
}

/**
 * is_delim - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string to compare against.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	int is_delimiter = 0; /* Initialize result to not a delimiter */

	while (*delim)
	{
		if (*delim++ == c)
		{
			is_delimiter = 1; /* Set to 1 if character is a delimiter */
			break;
		}
	}

	return (is_delimiter);
}


