#include "../headers/input_execution.h"

void	execute_input(t_data *data)
{
	//while parsing list of commands
	if (is_exit_command(data.input))
		break ;
	if (is_a_valid_command(&data))
		execute_command(&data);
	else
		printf("%s: command not found\n", data.input);
}
