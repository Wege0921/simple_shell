#include "shell.h"

/**
 * _myexit - Exits the shell with a specified exit status.
 * @info: Pointer to the info_t structure
 *	containing arguments and status.
 *
 * Return: Exits with the provided exit status.
 *	If info->argv[1] is not "exit",it returns 0.
 *	If an illegal number is provided, it sets info->status to 2
 * and returns 1.
 */
int _myexit(info_t *info)
{
	int exit_status;

	if (info->argv[1])  /* Check if an exit argument is provided */
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
	}
	info->err_num = _erratoi(info->argv[1]);
	return (-2);
	}
	info->err_num = -1;
	return (-2);
}



