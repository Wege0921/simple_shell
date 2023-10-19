#include "shell.h"

/**
 * find_cmd - Find a command in the PATH or based on the input.
 * @info: The info struct containing parameters and return values.
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, num_non_delim_tokens = 0;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			num_non_delim_tokens++;
	if (!num_non_delim_tokens)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

