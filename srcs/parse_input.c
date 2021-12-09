#include "../headers/parse_input.h"

/*
**	1) Starts by creating a starting leaf_node (if further on it discovers a
**	pipe or an ampersand, then it will create a starting branch_node and this
**	first leaf node will become the branch_node's left leaf_node (see types.h).
**	2) The current_node will be the node that it will be working on. That way,
**	data->tree will keep pointing to the tree starting point.
**	3) The parser will work as long as there's input to parse. The iteration is
**	made by the called functions themselves.
**	4) The input is white-space insensitive, so it can skip white space. If it
**	finds a special char ('|', '&', '<', '>') it handles it, otherwise it reads
**	arguments (the first of which should be a command).
**	5) After parsing all the input, checks if the flag data->escaped is on,
**	which would mean that the last character was a non-escaped escape char, aka
**	a new_line char. i
**	5) Before saving the new_arg, checks if the input has ended and, if so, if
**	the last char was an escape char. If that's the case, it throws an error
**	message, since according to the subject, the nl char is not supposed to be
**	interpreted.
*/

void	parse_input(t_data *data)
{
	t_tree 	*current_node;
	int		i;

	if (!data->input)
		return ;
	data->tree = init_leaf_node(NULL);
	current_node = data->tree;
	i = 0;
	while (data->input[i] != '\0')
	{
		skip_white_space(data->input, &i);
		if (data->input[i] == '|')
			handle_pipe(&current_node, data->input, &i);
		else if (data->input[i] == '&')
			handle_amper(&current_node, data->input, &i);
		else if (data->input[i] == '<')
			handle_input_redirection(&current_node, data, &i);
		else if (data->input[i] == '>')
			handle_output_redirection(&current_node, data, &i);
		else
			read_cmd_and_args(data, &current_node->leaf, &i);
	}
	if (data->escaped)
		terminate_program(SPECIAL_CHAR);
}

/*
**	Calls parser_core to get a new_argument and saves it to the matrix of the
**	current_node. In principle, the first argument should be a command. The
**	existence of this command (either as a builtin or in the system) will only
**	be checked later on during execution.
*/

void	read_cmd_and_args(t_data *data, t_leaf_node *current_node, int *i)
{
	char	*new_arg;

	new_arg = parser_core(data, i, true);
	if (new_arg)
		save_new_argument(current_node, new_arg);
}

/*
**	Parses through data->input starting at position *i, and until it either
**	finds the end of the input or an unescaped space char.
**	Since this function is called both to save arguments and to save redirection
**	addresses, it must receive a flag to inform whether it should interpret the
**	dollar_sign_char or not (it should not when reading the delimiter in heredoc
**	mode).
**	If it finds an escape_char, a quote_char or a dollar_sign, it calls the
**	appropriate function.
**	If it finds a non-escaped special_char, it also means the argument/
**	redirection address has finished and allow parse_input to handle it.
**	If it finds a non-escaped semicomma, it terminates the program, since
**	according to the subject, the semicomma is not supposed to be interpreted.
**	When it found a new argument/redirection address, it saves it to a string
**	and returns it.
*/

char	*parser_core(t_data *data, int *i, bool interpret_dollar)
{
	int old_i;
	char *str;

	old_i = *i;
	while (data->input[*i] != '\0'
		   && (!ft_isspace(data->input[*i])
			   || (ft_isspace(data->input[*i]) && data->escaped)))
	{
		if (is_escape_char(data->input[*i]))
			remove_escape_char(data, i);
		else if (is_quote_char(data->input[*i]))
			handle_quote_char(data, i);
		else if (is_dollar_sign(data->input[*i]) && interpret_dollar)
			handle_dollar_sign(data, i);
		else if (is_special_char(data->input[*i]) && !data->escaped)
			break;
		else if (is_semicomma(data->input[*i]) && !data->escaped)
			terminate_program(SPECIAL_CHAR);
		else
		{
			data->escaped = false;
			(*i)++;
		}
	}
	str = NULL;
	if (*i != old_i)
		str = ft_substr(data->input, old_i, *i - old_i);
	return (str);
}
