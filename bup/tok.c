#include "shell.h"

/**
 * **strtow - Split a string into words, ignoring repeated delimiters
 * @str: The input string
 * @d: The delimiter string
 * Return: A pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int l, m, n, o, p = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (l = 0; str[l] != '\0'; l++)
		if (!is_delim(str[l], d) && (is_delim(str[l + 1], d) || !str[l + 1]))
			p++;

	if (p == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, m = 0; m < p; m++)
	{
		while (is_delim(str[l], d))
			l++;
		n = 0;
		while (!is_delim(str[l + n], d) && str[l + n])
			n++;
		s[m] = malloc((n + 1) * sizeof(char));
		if (!s[m])
		{
			for (n = 0; n < m; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (m = 0; o < n; o++)
			s[m][o] = str[l++];
		s[m][o] = 0;
	}
	s[m] = NULL;
	return (s);
}

