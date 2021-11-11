#include "../headers/init.h"

void	init_data(t_data *data, int argc, char **argv)
{
	if (argc > 1)
		exit(0);
	(void) argv;
	data->input = NULL;
	data->paths = NULL;
//	data->nb_paths = 0;
	data->tree = NULL;
	data->exit_cmd = false;
}

void	init_cmd_node(t_data *data, t_node **branch)
{
	*branch = NULL;
	*branch = malloc(sizeof(t_node));
	if (!*branch)
		terminate_program(MALLOC, data);
	(*branch)->cmd_node.cmd = NULL;
	(*branch)->cmd_node.redir_input = NULL;
	(*branch)->cmd_node.redir_output = NULL;
	(*branch)->cmd_node.args = NULL;
}

void	init_op_node(t_data *data, t_node **branch)
{
	(*branch)->op_node.operator = 0;
	(*branch)->op_node.left = NULL;
	(*branch)->op_node.right = NULL;
}
