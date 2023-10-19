#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Find a builtin command.
 * @info: The info struct containing parameters and return values.
 *
 * Return: -1 if the builtin command is not found,
 *         0 if the builtin command is executed successfully,
 *         1 if the builtin command is found but not successful,
 *         -2 if the builtin command signals exit()
 */
int find_builtin(info_t *info)
{
	int index, result = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (index = 0; builtintbl[index].type; index++)
	{
		if (_strcmp(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			result = builtintbl[index].func(info);
			break;
		}
	}
	return (result);
}


/**
 * fork_cmd - Forks a child process to run a command.
 * @info: The info struct containing parameters and return values.
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: Replace with custom error handling function */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		/* Child process*/
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);/* Replace with custom error handling function*/
	}
	/* TODO: PUT ERROR FUNCTION */
	else
	{
		/* Parent process*/
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}


