#include "shell.h"

/**
 * input_buf - Buffer input for chained commands and read from stdin
 * @info: Pointer to the parameter structure
 * @buf: Pointer to the address of the input buffer
 * @len: Pointer to the length of the buffer
 *
 * This function buffers input for chained commands and reads from stdin.
 * It checks if there is anything left in the buffer, and if not, it fills it.
 * It also removes trailing newlines, handles comments, and updates the
 * history list if necessary.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t length_p = 0;

	if (!*len) /* If nothing is left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buf, &length_p, stdin);
#else
		bytes_read = _getline(info, buf, &length_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) Is this a command chain? */
			{
				*len = bytes_read;
				info->cmd_buf = buf;
			}
		}
	}
	return (bytes_read);
}

/**
 * sigintHandler - Signal handler for handling Ctrl-C (SIGINT)
 * @sig_num: The signal number (unused)
 *
 * This function handles the Ctrl-C signal (SIGINT) by printing a newline,
 * displaying the shell prompt, and flushing the buffer.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

#include "shell.h"
/**
 * get_input - Read a line without newline character
 * @info: Parameter structure
 *
 * This function reads a line of input from the user,
 * excluding the newline character.
 *
 * Return: The number of bytes read or -1 on EOF.
 */
ssize_t get_input(info_t *info)
{
	static char *chain_buf; /* Command chain buffer */
	static size_t current, iterator, length;
	ssize_t bytes_read = 0;
	char **arg_buf = &(info->arg), *current_ptr;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &chain_buf, &length);
	if (bytes_read == -1) /* EOF */
		return (-1);

	if (length) /* Commands left in the chain buffer */
	{
		iterator = current;
		current_ptr = chain_buf + current; /* Get a pointer for return */

		check_chain(info, chain_buf, &iterator, current, length);
		while (iterator < length) /* Iterate to a semicolon or the end */
		{
			if (is_chain(info, chain_buf, &iterator))
				break;
			iterator++;
		}

		current = iterator + 1; /* Increment past the nulled semicolon */
		if (current >= length) /* Reached the end of the buffer? */
		{
			current = length = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*arg_buf = current_ptr;
		return (_strlen(current_ptr)); /* Return the length of the current command */
	}
	*arg_buf = chain_buf; /* Not a chain; pass back the buffer from _getline() */
	return (bytes_read); /* Return the number of bytes read from _getline() */
}

/**
 * read_buf - Read data into a buffer
 * @info: Parameter structure
 * @buf: Buffer to store read data
 * @i: Pointer to the size of the buffer
 *
 * This function reads data into the provided buffer and updates the size.
 *
 * Return: The number of bytes read, or 0 if 'i' is non-zero.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return (0);
	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*i = bytes_read;
	return (bytes_read);
}

/**
 * _getline - Read the next line of input from STDIN
 * @info: Parameter structure
 * @ptr: Pointer to a buffer, preallocated or NULL
 * @length: Size of the preallocated 'ptr' buffer if not NULL
 *
 * This function reads the next line of input from STDIN and
 *	returns the number of characters read.
 * Return: The number of characters read, or -1 on error.
 */


int _getline(info_t *info, char **ptr, size_t *length)
{
	static char input_buffer[READ_BUF_SIZE];
	static size_t buffer_index, buffer_length;
	size_t k;
	ssize_t bytes_read = 0, tot = 0;
	char *current_ptr = NULL, *new_ptr = NULL, *newline;

	current_ptr = *ptr;

	if (current_ptr && length)
		tot = *length;

	if (buffer_index == buffer_length)
		buffer_index = buffer_length = 0;

	bytes_read = read_buf(info, input_buffer, &buffer_length);

	if (bytes_read == -1 || (bytes_read == 0 && buffer_length == 0))
		return (-1);

	newline = _strchr(input_buffer + buffer_index, '\n');
	k = newline ? 1 + (size_t)(newline - input_buffer) : buffer_length;

	new_ptr = _realloc(current_ptr, tot, tot ? tot + k : k + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (current_ptr ? free(current_ptr), -1 : -1);

	if (tot)
		_strncat(new_ptr, input_buffer + buffer_index, k - buffer_index);
	else
		_strncpy(new_ptr, input_buffer + buffer_index, k - buffer_index + 1);

	tot += k - buffer_index;
	buffer_index = k;
	current_ptr = new_ptr;

	if (length)
		*length = tot;
	*ptr = current_ptr;
	return (tot);
}

