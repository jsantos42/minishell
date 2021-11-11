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

void	handle_pipe(t_tree **current_node, char **str)
{
	int	operator;

	operator = PIPE;
	(*str)++;
	if (**str == '|')
	{
		operator = OR;
		(*str)++;
	}
	relink(current_node, operator);
}

void	handle_amper(t_tree **current_node, char **str)
{
	int	operator;

	operator = 0;
	(*str)++;
	if (**str == '&')
	{
		operator = AND;
		(*str)++;
	}
	else
		terminate_program(RUN_BG);
	relink(current_node, operator);
}


///this function needs renaming
/*
 * create new branch node
 * (*current_node)->previous->branch.right = branch_node;
 * branch_node->left = *current_node
 * *current_node = branch_node->right;
 */
void	relink(t_tree **current_node, int operator)
{
	t_data	*data;
	t_tree	*branch_node;
	t_tree	*new_leaf_node;

	data = get_data(NULL);
	branch_node = init_branch_node((*current_node)->previous);
	new_leaf_node = init_leaf_node(branch_node);
	if ((*current_node)->previous)
		(*current_node)->previous->branch.right = branch_node;
	else
		data->tree = branch_node;
	(*current_node)->previous = branch_node;
	branch_node->branch.left = *current_node;
	branch_node->branch.right = new_leaf_node;
	branch_node->branch.operator = operator;
	*current_node = branch_node->branch.right;
}




///*
// *	Creates a new branch_node and a new_leaf_node. Assigns the operator to the
// *	branch node according to the chars in the input string str. If it
// * create new branch node
// * (*current_node)->previous->branch.right = branch_node;
// * branch_node->left = *current_node
// * *current_node = branch_node->right;
// */
//void	handle_pipe_ampersand(t_tree **current_node, char **str, int operator)
//{
//	t_tree	*branch_node;
//	t_tree	*new_leaf_node;
//
//	branch_node = init_branch_node((*current_node)->previous);
//	new_leaf_node = init_leaf_node(branch_node);
//	if (**str != *(*str + 1))
//	{
//		branch_node->branch.operator = operator;
//		(*str)++;
//	}
//	else if (**str == '|')
//	{
//		branch_node->branch.operator = OR;
//		(*str) += 2;
//	}
//	else
//		terminate_program(RUN_BG);
//	(*current_node)->previous->branch.right = branch_node;
//	branch_node->branch.left = *current_node;
//	branch_node->branch.right = new_leaf_node;
//	*current_node = branch_node->branch.right;
//}












void	handle_redirection(t_data *data, char **str)
{
	(void)data;
	(void)str;
	//check for next char to be different than this one
	//save operation

}
