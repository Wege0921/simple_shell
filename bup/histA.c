#include "shell.h"

/**
 * read_history - Read command history from a file
 * @info: Parameter structure
 *
 * This function reads command history from
 *	a file and stores it in the 'info' structure.
 *
 * Return: The number of commands read on success, or 0 on failure.
 */



int read_history(info_t *info)
{
	int i, l = 0, c = 0;
	ssize_t f, r, s = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	f = open(filename, O_RDONLY);
	free(filename);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		s = st.st_size;
	if (s < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	r = read(f, buf, s);
	buf[s] = 0;
	if (r <= 0)
		return (free(buf), 0);
	close(f);
	for (i = 0; i < s; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf +, c++);
			l = i + 1;
		}
	if (l != i)
		build_history_list(info, buf + l, c++);
	free(buf);
	info->histcount = c;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}


/**
 * build_history_list - Add an entry to the history linked list
 * @info: Parameter structure
 * @buf: Buffer containing the command to add
 * @linecount: The history linecount (histcount)
 *
 * This function adds a new entry to the command history linked list.
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *new_node = NULL;

	if (info->history)
		new_node = info->history;
	add_node_end(&new_node, buf, linecount);

	if (!info->history)
		info->history = new_node;
	return (0);
}


/**
 * renumber_history - Renumber the history linked list after changes
 * @info: Parameter structure
 *
 * This function renumbers the history linked list after changes to the list.
 *
 * Return: The new histcount
 */
int renumber_history(info_t *info)
{
	list_t *current_node = info->history;
	int new_histcount = 0;

	while (current_node)
	{
		current_node->num = new_histcount++;
		current_node = current_node->next;
	}

	return (info->histcount = new_histcount);
}

