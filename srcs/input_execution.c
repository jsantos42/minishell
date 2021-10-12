#include "../headers/input_execution.h"

void	execute_input(t_data *data)
{
	int	iter;

	printf("The arguments you gave me:\n");
	iter = -1;
	while (++iter < data->commands->nb_args)
		printf("%s\n", data->commands->args[iter]);
//	//while parsing list of commands
//	if (is_exit_command(data->input))
//	{
//		data->exit_cmd = true;
//		break;
//	}
//	if (is_a_valid_command(&data))
//		execute_command(&data);
//	else
//		printf("%s: command not found\n", data.input);
}
