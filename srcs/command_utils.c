#include "../headers/command_utils.h"


int	is_exit_command(char *input)
{
	if (!ft_strncmp(input, "exit", 5))
	{
		printf("%s\n", input);
		return (1);
	}
	return (0);
}

void	execute_command(t_data *data)
{
	(void)data;
//	execve();

}


