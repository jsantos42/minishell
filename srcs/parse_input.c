#include "../headers/parse_input.h"

/*
**	1) Starts by creating a starting leaf_node (if further on it discovers a
**	pipe or an ampersand, then it will create a starting branch_node and this
**	first leaf node will become the branch_node's left leaf_node (see types.h).
**	2) The current_node will be the node that it will be working on. That way,
**	data->tree will keep pointing to the tree starting point. The same reasoning
**	applies to str, which will point to the current char to be parsed.
**	3) The parser will work as long as there's input to parse and the input is
**	legal.
**	4) The input is white-space insensitive, so it can skip white space. If it
**	finds a special char ('|', '&', '<', '>', '\\', ';') it handles it,
**	otherwise it reads arguments (the first of which should be a command).
*/

int	parse_input(t_data *data)
{
	t_tree 	*current_node;
	char	*str;

	data->tree = init_leaf_node(NULL);
	current_node = data->tree;
	str = data->input;
	while (*str != '\0' && !data->illegal_input)
	{
		str += skip_white_space(str);
		if (*str == '\\' || *str == ';')
			terminate_program(SPECIAL_CHAR);
		else if (*str == '|')
			handle_pipe(&current_node, &str);
		else if (*str == '&')
			handle_amper(&current_node, &str);
		else if (*str == '<')
			handle_input_redirection(&current_node, &str);
		else if (*str == '>')
			handle_output_redirection(&current_node, &str);
//		else if (*str == '(')
			///missing condition for parenthesis
		else
			read_cmd_and_args(data, &current_node->leaf, &str);
	}
	if (data->illegal_input)
		return (0);
	return (1);
}

/*
**	Starts by checking if it's reading a command or argument. If the matrix
**	current_node->args is empty, it's reading the first argument of the node,
**	meaning it should be reading a command. Otherwise, it assumes it's reading
**	an argument and calls a somewhat similar function (read_argument). There are
**	two main differences between them:
**	1) In commands, quotes and variable expansion ('$') are not allowed, whereas
**	in arguments they should be handled.
**	2) The command must exist, hence here it calls is_a_valid_command before
**	saving it in the matrix.
*/

int	read_cmd_and_args(t_data *data, t_leaf_node *current_node, char **str)
{
	int		i;
	char	*cmd;

	if (current_node->args != NULL)
		return (read_argument(current_node, str));
	i = 0;
	while ((*str)[i] != '\0'
	&& !ft_isspace((*str)[i]) && !is_special_char((*str)[i])
	&& !is_quote_char((*str)[i]) && !is_dollar_sign((*str)[i]))
		i++;
	cmd = ft_substr(*str, 0, i);
	if (is_a_valid_command(data, cmd))
	{
		save_new_argument(current_node, cmd);
		*str += i;
		return (1);
	}
	else
	{
		printf("minishell: %s: command not found\n", cmd);
		data->illegal_input	= true;
		free(cmd);
		return (0);
	}
}

/*
**	See comment of the previous function.
**	Note that there's a check if i != 0 to avoid saving empty arguments.
*/

int	read_argument(t_leaf_node *current_node, char **str)
{
	int i;
	char	*new_arg;

	i = 0;
	while ((*str)[i] != '\0'
	&& !ft_isspace((*str)[i]) && !is_special_char((*str)[i]))
	{
		if (is_quote_char((*str)[i]))
			*str = handle_quote_char(*str, &i);
		else if (is_dollar_sign((*str)[i]))
			*str = handle_dollar_sign(*str, &i);
		i++;
	}
	if (i != 0)
	{
		new_arg = ft_substr(*str, 0, i);
		save_new_argument(current_node, new_arg);
		*str += i;
	}
	return (1);
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