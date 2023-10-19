#include "shell.h"

/**
 * strtow2 - Splits a string into words using a specified delimiter
 * @str: The input string to split
 * @d: The delimiter character
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */

char **strtow2(char *str, char d)
{
	int l, m, n, o, p = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (l = 0; str[l] != '\0'; l++)
		if ((str[l] != d && str[l + 1] == d) ||
		    (str[l] != d && !str[l + 1]) || str[l + 1] == d)
			p++;
	if (p == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, m = 0; m < p; m++)
	{
		while (str[l] == d && str[l] != d)
			l++;
		n = 0;
		while (str[l + n] != d && str[l + n] && str[l + n] != d)
			n++;
		s[m] = malloc((n + 1) * sizeof(char));
		if (!s[m])
		{
			for (n = 0; n < m; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (o = 0; o < n; o++)
			s[m][o] = str[l++];
		s[m][o] = 0;
	}
	s[m] = NULL;
	return (s);
}
