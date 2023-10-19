
#include "shell.h"

/**
 * _myhistory - Display the history list with line numbers.
 * @info: Pointer to the info_t structure
 *      containing potential arguments.
 *
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
        print_list(info->history);
        return (0);
}
/**
 * unset_alias - Unset an alias associated with a given string.
 * @info: Pointer to the info_t structure containing parameters.
 * @str: The alias string to unset.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
        char *equal_sign, saved_char;
        int result;

        equal_sign = _strchr(str, '=');
        if (!equal_sign)
                return (1);

        saved_char = *equal_sign;
        *equal_sign = '\0';
        result = delete_node_at_index(&(info->alias),
                get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
        *equal_sign = saved_char;

        return (result);
}


/**
 * set_alias - Set an alias for a given string.
 * @info: Pointer to the info_t structure containing parameters.
 * @str: The string alias to set.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *equal_sign;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return (1);

	if (!*++equal_sign)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias string.
 * @node: The alias node containing the alias string.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *equal_sign = NULL, *alias = NULL;

	if (node)
	{
		equal_sign = _strchr(node->str, '=');
		for (alias = node->str; alias <= equal_sign; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the alias built-in command.
 * @info: Pointer to the info_t structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

