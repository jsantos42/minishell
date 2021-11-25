#include "../headers/builtins.h"

void	builtin_echo(char **args, int *ctx)
{
	int		iter;
	bool	new_line;
	bool	print_space;
	
	iter = 1;
	if (args[iter] && !ft_strncmp(args[iter], "-n", 3))
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
			write(ctx[1], " ", 1);
		else
			print_space = true;
		write(ctx[1], args[iter], ft_strlen(args[iter]));
		iter++;
	}
	if (new_line)
		write(ctx[1], "\n", 1);
}

void	builtin_cd(char **args)
{
	chdir(args[1]);
}