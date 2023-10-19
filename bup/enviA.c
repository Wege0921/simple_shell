#include "shell.h"

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Pointer to the info_t structure containing potential arguments.
 *
 * Return: Always 0 on success, 1 on error.
 */
int _myunsetenv(info_t *info)
{
	int arg_index;

	/* Check if there are enough arguments */
	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	/* Iterate through the arguments and unset each environment variable */
	for (arg_index = 1; arg_index <= info->argc; arg_index++)
		_unsetenv(info, info->argv[arg_index]);

	return (0);
}

/**
 * populate_env_list - Populate the environment linked list.
 * @info: Pointer to the info_t structure containing potential arguments.
 *
 * Return: Always 0 on success.
 */
int populate_env_list(info_t *info)
{
	list_t *env_node = NULL;
	size_t index;

	/* Populate the environment linked list from the 'environ' array */
	for (index = 0; environ[index]; index++)
		add_node_end(&env_node, environ[index], 0);

	info->env = env_node;
	return (0);
}

