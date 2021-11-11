#include "../headers/handle_special_chars.h"

int	skip_white_space(char *input)
{
	int	iter;

	iter = -1;
	while (input[++iter] != '\0')
	{
		if (!ft_isspace(input[iter]))
			break ;
	}
	return (iter);
}

int	handle_dollar_sign(t_data *data, char **str)
{
	//this must finish on a space or special char
	(void)data;
	(void)str;
	return (0);
}

void	handle_pipe(t_data *data, t_tree **current_node, char **str)
{
	t_leaf_node 	*new_leaf_node;
	t_branch_node 	*branch_node;

	/*
	 * create new branch node
	 * (*current_node)->previous->branch.right = branch_node;
	 * branch_node->left = *current_node
	 * *current_node = branch_node->right;
	 */

	if (**str == *(*str + 1))
	{
		(*current_node)->operator = OR;
		(*str) += 2;
	}
	else
	{
		(*current_node)->operator = PIPE;
		(*str)++;
	}
	new_cmd_node = NULL;
	init_cmd_node(data, &new_command);
	(*current_node)->right = new_command;
	*current_node = (*current_node)->right;
}

void	handle_amper(t_data *data, t_cmd **current_node, char **str)
{
	t_cmd	*new_command;

	if (**str == *(*str + 1))
	{
		(*current_node)->operator = AND;
		(*str) += 2;
	}
	else
		terminate_program(RUN_BG, data);
	new_command = NULL;
	init_cmd_node(data, &new_command);
	(*current_node)->right = new_command;
	*current_node = (*current_node)->right;
}

void	handle_redirection(t_data *data, char **str)
{
	(void)data;
	(void)str;
	//check for next char to be different than this one
	//save operation

}
