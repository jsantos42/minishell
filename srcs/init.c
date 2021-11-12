#include "../headers/init.h"

void	init_data(t_data *data, int argc, char **argv)
{
	if (argc > 1)
		exit(0);
	(void) argv;
	data->input = NULL;
	data->paths = NULL;
	data->nb_paths = 0;
	data->tree = NULL;
	data->exit_cmd = false;
	get_data(data);
}

t_tree	*init_leaf_node(t_tree *previous)
{
	t_tree	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		terminate_program(MALLOC);
	new_node->leaf.cmd = NULL;
	new_node->leaf.args = NULL;
	new_node->leaf.nb_args = 0;
	new_node->leaf.redir_input = NULL;
	new_node->leaf.redir_output = NULL;
	new_node->leaf.append_mode = false;
	new_node->leaf.here_doc = false;
	new_node->leaf.delimiter = NULL;
	new_node->previous = previous;
	return (new_node);
}

t_tree	*init_branch_node(t_tree *previous)
{
	t_tree	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		terminate_program(MALLOC);
	new_node->branch.operator = 0;
	new_node->branch.left = NULL;
	new_node->branch.right = NULL;
	new_node->previous = previous;
	return (new_node);
}
