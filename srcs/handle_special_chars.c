#include "../headers/handle_special_chars.h"

int	skip_white_space(char *input)
{
	int	i;

	i = -1;
	while (input[++i] != '\0')
	{
		if (!ft_isspace(input[i]))
			break ;
	}
	return (i);
}

char	*handle_dollar_sign(char *input, int *dollar_pos)
{
	//this must finish on a space or special char
	(void)input;
	(void)dollar_pos;
	return (input);//must return new_input
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
	int	i;

	(*str)++;
	if (**str == '>')
	{
		(*current_node)->leaf.append_mode = true;
		(*str)++;
	}
	*str += skip_white_space(*str);
	i = -1;
	while ((*str)[++i] != '\0'
	&& !is_special_char((*str)[i])
	&& !ft_isspace((*str)[i]))
	{
		if (is_quote_char((*str)[i]))
			*str = handle_quote_char(*str, &i);
		else if (is_dollar_sign((*str)[i]))
			*str = handle_dollar_sign(*str, &i);
	}
	if (i != 0)
		(*current_node)->leaf.redir_output = ft_substr(*str, 0, i);
	*str += i;
}

/*
**	This makes sure nothing between quotes gets interpreted as a command.
**	1) It starts by defining which type of quote it's using.
**	2) Creates a new_input string, which will be a copy of input without the
**	pair of quotes it's handling.
**	3) Parses through the input string and copies it to new_input, except for
**	the quote_type char (unless it's escaped). Continues to do so until it finds
**	a closing quote.
**	4) If it found a closing quote, saves the new position (that will be passed
**	to scanner->cursor) and copies the rest of the input string to new_input,
**	NULL-terminating it and returning it.
**	NOTE: when saving the new quote_pos, it uses k (instead of i) because
**	it needs to subtract 2 quote chars from the index count. Plus, it needs to
**	subtract 1 because the iteration on the previous while goes one extra loop.
*/

char	*handle_quote_char(char *input, int *quote_pos)
{
	char	quote_type;
	char	*new_input;
	int 	quotes_found;
	int		i;
	int		k;

	quote_type = *(input + *quote_pos);
	new_input = malloc(ft_strlen(input) - PAIR_OF_QUOTES + 1);
	if (!new_input)
		terminate_program(MALLOC);
	quotes_found = 0;
	i = 0;
	k = 0;
	while (input[i] != '\0' && quotes_found < 2)
	{
		if (!(input[i] == quote_type
			  && (i == 0 || input[i - 1] != '\\')))
			new_input[k++] = input[i];
		else
			(quotes_found)++;
		i++;
	}
	if (quotes_found < 2)
	{
		free(new_input);
		terminate_program(UNCLOSED_QUOTES);
	}
	else
	{
		*quote_pos += k - 1;
		while (input[i] != '\0')
			new_input[k++] = input[i++];
		new_input[k] = '\0';
	}
	free(input);
	return (new_input);
}
