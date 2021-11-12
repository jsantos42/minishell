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



/// has to output error when the next char is a PIPE or an AMPERSAND or a third >>>

void	handle_input_redirection(t_tree **current_node, char **str)
{
	(void)current_node;
	(void)str;
//	(*str++);
//	if
//
//	(void)str;
//	//check for next char to be different than this one
//	//save operation

}



void	handle_output_redirection(t_tree **current_node, char **str)
{
	int	iter;

	(*str)++;
	if (**str == '>')
	{
		(*current_node)->leaf.append_mode = true;
		(*str)++;
	}
	*str += skip_white_space(*str);
	iter = -1;
	while ((*str)[++iter] != '\0' && !is_special_char((*str)[iter]))
	{
		if (is_quote_char((*str)[iter]))
			iter += advance_to_closing_quote(*str + iter);
		else if (is_dollar_char((*str)[iter]))
			iter += handle_dollar_sign(NULL, str + iter); //rewrite this
		else if (ft_isspace((*str)[iter]))
			break ;
	}
	if (iter != 0)
		(*current_node)->leaf.redir_output = ft_substr(*str, 0, iter);
	*str += iter;
	*str += skip_white_space(*str);
}













