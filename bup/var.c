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
