#include "shell.h"

/**
 * get_history_file - Get the path to the history file
 * @info: Parameter structure
 *
 * This function constructs the path to the history file based
 *	on the user's home directory.
 *
 * Return: Allocated string containing the path to the
 *	history file, or NULL on failure.
 */
char *get_history_file(info_t *info)
{
	char *home_dir, *h_path;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);

	h_path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!h_path)
		return (NULL);

	h_path[0] = 0;
	_strcpy(h_path, home_dir);
	_strcat(h_path, "/");
	_strcat(h_path, HIST_FILE);

	return (h_path);
}


/**
 * write_history - Write command history to a file
 * @info: Parameter structure
 *
 * This function creates a file or appends to an existing file to
 *	store the command history.
 *
 * Return: 1 on success, or -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t file_descriptor;
	char *file_name = get_history_file(info);
	list_t *c_node = NULL;

	if (!file_name)
		return (-1);

	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_descriptor == -1)
		return (-1);

	for (c_node = info->history; c_node; c_node = c_node->next)
	{
		_putsfd(c_node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}

	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}



