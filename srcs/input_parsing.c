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
	t_cmd	*current_command;
	char	*str;

	init_command(data, &data->commands);
	current_command = data->commands;
	str = data->input;
	while (*str != '\0')
	{
		if (!read_command(data, current_command, &str)
		|| !read_argument(data, current_command, &str))
			return (0);
		if (*str == '\\' || *str == ';')
			terminate_program(SPECIAL_CHAR, data);
		else if (*str == '|')
		{
			handle_pipe(data, &str);
			current_command = current_command->next;
			init_command(data, &current_command);
		}
		else if (*str == '&')
		{
			handle_amper(data, &str);
			current_command = current_command->next;
			init_command(data, &current_command);
		}
		else if (*str == '<' || *str == '>')
			handle_redirection(data, &str);
	}
	return (1);
}

/*
**	In the beginning it checks whether command has already been saved; if so, it
**	moves on and assumes it is meant to read an argument.
*/

int	read_command(t_data *data, t_cmd *command, char **str)
{
	int		iter;
	char	*cmd;

	*str += handle_white_space(*str);
	if (command->cmd != NULL)
		return (1);
	iter = 0;
	while ((*str)[iter] != '\0'
	&& !is_special_char((*str)[iter])
	&& !ft_isspace((*str)[iter]))
		iter++;
	cmd = ft_substr(*str, 0, iter);
	if (is_a_valid_command(data, cmd))
	{
		command->cmd = cmd;
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

int	read_argument(t_data *data, t_cmd *command, char **str)
{
	int iter;

	*str += handle_white_space(*str);
	iter = -1;
	while ((*str)[++iter] != '\0')
	{
		if ((*str)[iter] == '\'' || (*str)[iter] == '\"')
			iter += advance_to_closing_quote(data, *str + iter);
		else if ((*str)[iter] == '$')
			iter += handle_dollar_sign(data, str + iter);
		else if (is_special_char((*str)[iter]))
			break ;
		else if (ft_isspace((*str)[iter]))
		{
			save_new_argument(data, command, str, iter); //updates the str pointer position
			*str += handle_white_space(*str);
			iter = -1;
		}
	}
	save_new_argument(data, command, str, iter); //updates the str pointer position
	return (1);
}

/*
**	Creates a new matrix, allocating enough memory to contain both the previous
**	allocated argument strings* and the new argument. Frees the previous
**	allocated matrix* and makes command args point to this new matrix. Finally,
**	it increases the number of arguments and advances the original string until
**	the end char.
**
**	*in case it's not the first time it's called.
*/

void	save_new_argument(t_data *data, t_cmd *command, char **str, int end)
{
	char	**new;
	int		iter;

	new = NULL;
	new = malloc(sizeof(char *) * (command->nb_args + 1));
	if (!new)
		terminate_program(MALLOC, data);
	iter = -1;
	while (++iter < command->nb_args)
		new[iter] = command->args[iter];
	new[iter] = ft_substr(*str, 0, end);
	free_if_not_null(command->args);
	command->args = new;
	command->nb_args++;
	*str += end;
}


//int	check_how_many_commands(char *input)
//{
//	size_t	pipe_nb;
//	size_t	amper_nb;
//	size_t	squote_nb;
//	size_t	dquote_nb;
//	size_t	langle_nb;
//	size_t	rangle_nb;
//	int		*pipe_pos;
//	int		*amper_pos;
//	int		*squote_pos;
//	int		*dquote_pos;
//	int		*langle_pos;
//	int		*rangle_pos;
//
//	if (count_chr_instances(input, '\\') || count_chr_instances(input, ';'))
//		terminate_program(SPECIAL_CHAR, data); //only if not inside quotes!!
//	pipe_pos = map_chr_instances(input, '|', &pipe_nb);
//	amper_pos = map_chr_instances(input, '&', &pipe_nb);
//	squote_pos = map_chr_instances(input, '\'', &pipe_nb);
//	dquote_pos = map_chr_instances(input, '\"', &pipe_nb);
//	langle_pos = map_chr_instances(input, '<', &langle_nb);
//	rangle_pos = map_chr_instances(input, '>', &rangle_nb);
//	if ((!pipe_pos && pipe_nb != 0)
//		|| (!amper_pos && amper_nb != 0)
//		|| (!squote_pos && squote_nb != 0)
//		|| (!dquote_pos && dquote_nb != 0)
//		|| (!langle_pos && langle_nb != 0)
//		|| (!rangle_pos && rangle_nb != 0))
//		terminate_program(MALLOC, data);
//
//	return (1);
//}
