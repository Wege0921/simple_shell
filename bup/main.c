#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	/* Initialize an info_t struct with default values. */
	info_t info[] = { INFO_INIT };
	int f = 2;

	/* Using inline assembly it performs a simple operation. */
	asm (
		"mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (f)
		: "r" (f)
	);
	/* Check if a command-line argument is provided. */
	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = f;
	}
	/* Populate the environment list in the info struct. */
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	 /* Return 0 on successful execution. */
	return (EXIT_SUCCESS);
}

