#include "shell.h"

/**
 * is_cmd - Determines if a file at the given path is
 *	an executable command.
 * @info: The info struct (not currently used).
 * @path: The path to the file.
 *
 * Return: 1 if it's an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat file_stat;

	(void)info;
	if (!path || stat(path, &file_stat))
		return (0);

	if (S_ISREG(file_stat.st_mode))
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicate characters from a string within a specified range.
 * @pathstr: The source string.
 * @start: The starting index of the range.
 * @stop: The stopping index of the range.
 *
 * Return: A pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char duplicated_buffer[1024];/* Buffer for duplicated characters */
	int buffer_index = 0;  /* Index for the duplicated_buffer */
	int string_index = 0;  /* Index for the source string */

	for (string_index = start; string_index < stop; string_index++)
	{
		if (pathstr[string_index] != ':')
		{
			duplicated_buffer[buffer_index++] = pathstr[string_index];
		}
	}
	duplicated_buffer[buffer_index] = '\0';
	return (duplicated_buffer);
}


/**
 * find_path - Find the full path of a command in the PATH string.
 * @info: Pointer to the info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found,
 *	or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int str_index = 0, start_pos = 0;
	char *full_path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[str_index] || pathstr[str_index] == ':')
		{
			full_path = dup_chars(pathstr, start_pos, str_index);

			if (!*full_path)
				_strcat(full_path, cmd);
			else
			{
				_strcat(full_path, "/");
				_strcat(full_path, cmd);
			}

			if (is_cmd(info, full_path))
				return (full_path);

			if (!pathstr[str_index])
				break;
			start_pos = str_index;
		}
		str_index++;
	}

	return (NULL);
}

