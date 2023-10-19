#include "shell.h"

/**
 * _myenv - Print the current environment.
 * @info: Pointer to the info_t structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Get the value of an environment variable.
 * @info: Pointer to the info_t structure containing potential arguments.
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *env_node = info->env;
	char *value_ptr;

	while (env_node)
	{
		value_ptr = starts_with(env_node->str, name);
		if (value_ptr && *value_ptr)
			return (value_ptr);
		env_node = env_node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one.
 * @info: Pointer to the info_t structure containing potential arguments.
 *
 * Return: Always 0 on success, 1 on error.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

