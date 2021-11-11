#include "../headers/input_parsing.h"

/* alternative: locate the special chars from the start
 if '>' or '<', next is file_name
else is always command

if ('|'), it means new command

 in https://unix.stackexchange.com/questions/86247/what-does-ampersand-mean-at-the-end-of-a-shell-script-line
A && B means "run command B if command A succeeded", and A || B means "run command B if command A failed".
 Examples: 'cd tmp && ls' will run ls only if folder tmp exists. Or in a script: 'cd foobar || exit 10' will stop the
 execution (exit) if folder foobar doesnt' exist. –

		 * find location of first | and &
		 * then check if there are quotes and if their location surrounds the found pipe/ampersand
		 * 		make sure to check for both quotes types
		 * 		if no closing quotes, error (unless surrounded by quotes of the other type)
		 * if yes, ignore found |or& and find next one
		 * otherwise, read command until then
		 * then check next char to see if this was actually a pipe or a || sign
 */
int	parse_input(t_data *data)
{
	t_tree 	*current_node;
	char	*str;

	data->tree = init_leaf_node(NULL);
	current_node = data->tree;
	str = data->input;
	while (*str != '\0')
	{
		if (!read_command(data, &current_node->leaf, &str)
		|| !read_argument(data, &current_node->leaf, &str))
			return (0);
		if (*str == '\\' || *str == ';')
			terminate_program(SPECIAL_CHAR);
		else if (*str == '|')
			handle_pipe(&current_node, &str);
		else if (*str == '&')
			handle_amper(&current_node, &str);
		else if (*str == '<' || *str == '>')
			handle_redirection(data, &str);
	}
	return (1);
}

/*
**	In the beginning it checks whether command has already been saved; if so, it
**	assumes it is meant to read an argument and returns. Otherwise, tries to
**	read a command and checks if it is a valid one.
*/

int	read_command(t_data *data, t_leaf_node *current_node, char **str)
{
	int		iter;
	char	*cmd;

	*str += skip_white_space(*str);
	if (current_node->cmd != NULL)
		return (1);
	iter = 0;
	while ((*str)[iter] != '\0'
	&& !is_special_char((*str)[iter])
	&& !ft_isspace((*str)[iter]))
		iter++;
	cmd = ft_substr(*str, 0, iter);
	if (is_a_valid_command(data, cmd))
	{
		current_node->cmd = cmd;
		*str += iter;
		return (1);
	}
	else
	{
		printf("minishell: %s: command not found\n", cmd);
		free(cmd);
		return (0);
	}
}

int	read_argument(t_data *data, t_leaf_node *current_node, char **str)
{
	int iter;

	*str += skip_white_space(*str);
	iter = -1;
	while ((*str)[++iter] != '\0')
	{
		if ((*str)[iter] == '\'' || (*str)[iter] == '\"')
			iter += advance_to_closing_quote(*str + iter);
		else if ((*str)[iter] == '$')
			iter += handle_dollar_sign(data, str + iter);
		else if (is_special_char((*str)[iter]))
			break;
		else if (ft_isspace((*str)[iter]))
		{
			save_new_argument(current_node, str, iter); //updates the str pointer position
			*str += skip_white_space(*str);
			iter = -1;
		}
	}
	save_new_argument(current_node, str, iter); //updates the str pointer position
	return (1);
}



# define NEW_ARG	1
# define NULLTERM	1

///rename end var
/*
**	It should only save a new argument and increase the nb_args if there is
**	anything to save (that is, if there's at least 1 char to save).
**	Creates a new matrix, allocating enough memory to contain both the previous
**	allocated argument strings* and the new argument. Frees the previous
**	allocated matrix* and makes command args point to this new matrix. Finally,
**	it increases the number of arguments and advances the original string until
**	the end char.
**
**	*in case it's not the first time it's called.
*/

void	save_new_argument(t_leaf_node *current_node, char **str, int end)
{
	char	**new;
	int		iter;

	if (end != 0)
	{
		new = NULL;
		new = malloc(sizeof(char *) * (current_node->nb_args + NEW_ARG + NULLTERM));
		if (!new)
			terminate_program(MALLOC);
		iter = -1;
		while (++iter < current_node->nb_args)
			new[iter] = current_node->args[iter];
		new[iter] = ft_substr(*str, 0, end);
		new[++iter] = NULL;
		free_if_not_null(current_node->args);
		current_node->args = new;
		current_node->nb_args++;
		*str += end;
	}
}
