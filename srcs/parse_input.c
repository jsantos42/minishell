#include "../headers/parse_input.h"

/*
**	1) Starts by creating a starting leaf_node (if further on it discovers a
**	pipe or an ampersand, then it will create a starting branch_node and this
**	first leaf node will become the branch_node's left leaf_node (see types.h).
**	2) The current_node will be the node that it will be working on. That way,
**	data->tree will keep pointing to the tree starting point.
**	3) The parser will work as long as there's input to parse.
**	4) The input is white-space insensitive, so it can skip white space. If it
**	finds a special char ('|', '&', '<', '>') it handles it, otherwise it reads
**	arguments (the first of which should be a command).
*/

int	parse_input(t_data *data)
{
	t_tree 	*current_node;
	int		i;

	if (!data->input)
		return (0);
	data->tree = init_leaf_node(NULL);
	current_node = data->tree;
	i = 0;
	while (data->input[i] != '\0')
	{
		skip_white_space(data->input, &i);
//		if (is_escape_char(data->input[i]))
//			remove_escape_char(data, &i);
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
	return (1);
}

/*
**	Reads an argument until it either finds the end of the input or an
**	unescaped space char, both of which would mean the end of the current
**	argument.
**	If it finds a quote_char, it handles it (the protection against an escaped
**	quote_char is inside that function).
**	If it finds other escaped char, it removes it (note that it still iterates
**	to the next char, so the now unescaped char will not be interpreted).
**	If it finds a dollar sign, it expands the given variable name.
**	If it finds a semicomma or a special char it breaks, since it's the end of
**	that argument.
**	5) Before saving the new_arg, checks if the input has ended and, if so, if
**	the last char was an escape char. If that's the case, it calls the function
**	check_for_nl_char to decide whether to remove the escaped escape_char or to
**	throw an error message, since according to the subject, the nl char is not
**	supposed to be interpreted.
**
**	Note: in principle, the first argument should be a command. The existence of
**	this command (either as a builtin or in the system) will only be checked on
**	the execution part.
*/

void	read_cmd_and_args(t_data *data, t_leaf_node *current_node, int *i)
{
	int		old_i;
	char	*new_arg;

	old_i = *i;
	while (data->input[*i] != '\0' && (!ft_isspace(data->input[*i])
		|| (ft_isspace(data->input[*i]) && data->escaped)))
	{
		if (is_escape_char(data->input[*i]))
			remove_escape_char(data, i);
		else if (is_quote_char(data->input[*i]))
			handle_quote_char(data, i);
		else if (is_dollar_sign(data->input[*i]))
			handle_dollar_sign(data, i);
		else if (is_special_char(data->input[*i])) //missing protection against escape here
		{
			if (data->escaped)
				data->escaped = false;
			else
				break ;
		}
		else if (is_semicomma(data->input[*i]))
		{
			if (data->escaped)
			{
				data->escaped = false;
				i++;
			}
			else
				terminate_program(SPECIAL_CHAR);
		}
		else
		{
			data->escaped = false;
			(*i)++;
		}
	}
	if (*i != old_i) ///this gets an advance old_i
	{
		new_arg = ft_substr(data->input, old_i, *i - old_i);
		save_new_argument(current_node, new_arg);
	}
}


/*
**	Creates a new_matrix, allocating enough memory to contain both the previous
**	allocated argument strings* and the new argument. Frees the previous
**	allocated matrix* and makes the current_node->args point to this new_matrix.
**	Finally, it increases the number of arguments (note that this nb_args
**	includes the command itself, which should be the first arg).
**
**	*in case it's not the first time it's called.
*/

void	save_new_argument(t_leaf_node *current_node, char *new_arg)
{
	char	**new_matrix;
	int		i;

	new_matrix = NULL;
	new_matrix = malloc(sizeof(char *) * (current_node->nb_args + NEW_ARG + NULLTERM));
	if (!new_matrix)
		terminate_program(MALLOC);
	i = -1;
	while (++i < current_node->nb_args)
		new_matrix[i] = current_node->args[i];
	new_matrix[i] = new_arg;
	new_matrix[++i] = NULL;
	free_if_not_null(current_node->args);
	current_node->args = new_matrix;
	current_node->nb_args++;
}