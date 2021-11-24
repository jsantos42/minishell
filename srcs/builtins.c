#include "../headers/builtins.h"

void	builtin_echo(char **args)
{
	int		iter;
	bool	new_line;
	bool	print_space;
	
	iter = 1;
	if (!ft_strncmp(args[iter], "-n", 3))
	{
		new_line = false;
		iter = 2;
	}
	else
		new_line = true;
	print_space = false;
	while (args[iter])
	{
		if (print_space)
			write(STDIN_FILENO, " ", 1);
		else
			print_space = true;
		write(STDIN_FILENO, args[iter], ft_strlen(args[iter]));
		iter++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
}

