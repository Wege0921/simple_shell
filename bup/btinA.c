#include "shell.h"

/**
 * _mycd - Change the current directory of the process.
 * @info: Pointer to the info_t structure
 *	containing potential arguments.
 *
 * Return: Always 0.
 */


int _mycd(info_t *info)
{
	char *cwd, *target_dir, buffer[1024];
	int ret;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure message here<<\n");

	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			ret = chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			ret = chdir(target_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		ret = chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		ret = chdir(info->argv[1]);

	if (ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	} return (0);
}
/**
 * _myhelp - Display help information.
 * @info: Pointer to the info_t structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
	char **arguments;

	arguments = info->argv;
	_puts("Help function is calle, functionality is not yet implemented.\n");
	if (0)
		_puts(*arguments); /* Temporary unused variable workaround */
	return (0);
}


