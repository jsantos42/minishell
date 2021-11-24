#include "main.h"

void	builtin_echo(char **args)
{
	ft_putstr_fd(args[1], 1);
}