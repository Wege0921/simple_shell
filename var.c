#include "shell.h"

/**
 * is_chain - Test if the current character in the
 *	buffer is a chain delimiter.
 * @info: The parameter and return information struct.
 * @buf: The character buffer.
 * @position: Address of the current position in the buffer.
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise.
 */




int is_chain(info_t *info, char *buf, size_t *position)
{
	size_t current_position = *position;

	if (buf[current_position] == '|' && buf[current_position + 1] == '|')
	{
		buf[current_position] = '\0';
		current_position++;
		info->cmd_buf_type = CMD_OR;
	} else if (buf[current_position] == '&' && buf[current_position + 1] == '&')
	{
		buf[current_position] = '\0';
		current_position++;
		info->cmd_buf_type = CMD_AND;
	} else if (buf[current_position] == ';')
	{ /* Found end of this command */
		buf[current_position] = '\0'; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	} else
	{
		return (0);
	}
	*position = current_position;
	return (1);
}

/**
 * check_chain - Checks whether chaining
 *	should continue based on the last status.
 * @info: The parameter & return information struct.
 * @buf: The character buffer containing the command.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * This function examines the command chaining type (AND, OR, or ;) and the
 * last command's exit status to decide if chaining should continue. If not,
 * it updates the buffer accordingly.
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t y = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}

	*p = y;
}
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
	int l = 0;
	list_t *node;

	for (l = 0; info->argv[l]; l++)
	{
		if (info->argv[l][0] != '$' || !info->argv[l][1])
			continue;

		if (!_strcmp(info->argv[l], "$?"))
		{
			replace_string(&(info->argv[l]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[l], "$$"))
		{
			replace_string(&(info->argv[l]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[l][1], '=');
		if (node)
		{
			replace_string(&(info->argv[l]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[l], _strdup(""));

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



