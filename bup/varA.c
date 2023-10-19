/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @info: The parameter & return information struct.
 *
 * This function searches for an alias that matches
 *	the command, replaces
 * the command with the alias value, and
 *	returns 1 if a replacement is made.
 * If no alias is found or memory allocation fails, it returns 0.
 *
 * Return: 1 if an alias is replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *alias_node;
	char *alias_value;

	for (i = 0; i < 10; i++)
	{
		alias_node = node_starts_with(info->alias, info->argv[0], '=');
		if (!alias_node)
			return (0);

		free(info->argv[0]);
		alias_value = _strchr(alias_node->str, '=');

		if (!alias_value)
			return (0);

		alias_value = _strdup(alias_value + 1);

		if (!alias_value)
			return (0);

		info->argv[0] = alias_value;
	}

	return (1);
}
/**
 * replace_vars - Replaces variables in the tokenized string.
 * @info: The parameter & return information struct.
 *
 * This function iterates through the tokenized string and replaces variables
 * with their corresponding values. It returns 1 if any replacement is made.
 * If no replacements are made, it returns 0.
 *
 * Return: 1 if any variables are replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(info->status, 10, 0));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]), _strdup(convert_number(getpid(), 10, 0));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info->argv[x]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));
	}

	return (0);
}

/**
 * replace_string - Replaces a string with a new one.
 * @old: Address of the old string.
 * @new: The new string to replace with.
 *
 * This function frees the old string and replaces it with the new one.
 * It returns 1 if the replacement is successful, and 0 if it fails.
 *
 * Return: 1 if the string is replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}



