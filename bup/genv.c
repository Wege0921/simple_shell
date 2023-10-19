#include "shell.h"

/**
 * get_environ - Get the environment variables as a string array
 * @info: A structure containing potential arguments and environment data
 *
 * This function returns a string array copy of the environment variables.
 * If the environment has changed or is not yet set, it converts the
 * linked list of environment variables to a string array and updates
 * the 'info' structure accordingly.
 *
 * Return: A pointer to the string array of environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: A structure containing potential arguments and environment data
 * @var: The string representing the environment variable to be removed
 *
 * This function removes the specified environment variable from the 'info'
 * structure, effectively unsetting it. It returns 1 on successful deletion
 * and 0 if the variable was not found.
 *
 * Return: 1 on successful deletion, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *current_node = info->env;
	size_t index = 0;
	char *match;

	if (!current_node || !var)
		return (0);

	while (current_node)
	{
		match = starts_with(current_node->str, var);
		if (match && *match == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			current_node = info->env;
			continue;
		}
		current_node = current_node->next;
		index++;
	}

	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one
 * @info: A structure containing potential arguments and environment data
 * @var: The name of the environment variable
 * @value: The value to set for the environment variable
 *
 * This function creates or updates an environment variable by setting its
 * name and value. If the variable already exists, it updates the value;
 * otherwise, it creates a new environment variable. The 'info' structure
 * is updated to reflect the change.
 *
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *new_env_var = NULL;
	list_t *current_node;
	char *match;

	if (!var || !value)
		return (0);

	new_env_var = malloc(_strlen(var) + _strlen(value) + 2);
	if (!new_env_var)
		return (1);

	_strcpy(new_env_var, var);
	_strcat(new_env_var, "=");
	_strcat(new_env_var, value);

	current_node = info->env;
	while (current_node)
	{
		match = starts_with(current_node->str, var);
		if (match && *match == '=')
		{
			free(current_node->str);
			current_node->str = new_env_var;
			info->env_changed = 1;
			return (0);
		}
		current_node = current_node->next;
	}

	add_node_end(&(info->env), new_env_var, 0);
	free(new_env_var);
	info->env_changed = 1;
	return (0);
}



