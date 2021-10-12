#include "../headers/init.h"

void	init_data(t_data *data, int argc, char **argv)
{
	if (argc > 1)
		exit(0);
	(void) argv;
	data->input = NULL;
	data->paths = NULL;
	data->nb_paths = 0;
	data->commands = NULL;
	data->exit_cmd = false;
}

void	init_command(t_data *data, t_cmd **command)
{
	*command = NULL;
	*command = malloc(sizeof(t_cmd));
	if (!*command)
		terminate_program(MALLOC, data);
	(*command)->cmd = NULL;
	(*command)->redir_input = NULL;
	(*command)->redir_output = NULL;
	(*command)->args = NULL;
	(*command)->args = NULL;
	(*command)->nb_args = 0;
	(*command)->relation_to_next = 0;
	(*command)->next = NULL;
}
