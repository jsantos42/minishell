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
void	parse_input(t_data *data)
{
	char	*str;
	int		iter;

	str = data->input;

	str += handle_white_space(str);
	command_iter = -1;
	while (*str != '\0')
	{
		//init data->cmd malloc!
		str += read_command(data, str);
		str += handle_white_space(str);
		str += read_argument(data, str);
		if (*str == '\\' || *str == ';')
			terminate_program(SPECIAL_CHAR, data);
		else if (*str == '|')
			str += handle_pipe(data, str);
		else if (*str == '&')
			str += handle_amper(data, str);
		else if (*str == '<' || *str == '>')
			str += handle_redirection(data, str);
	}
}

int	read_command(t_data *data, char *str)
{
	int		iter;
	char	*cmd;

	iter = 0;
	while (str[iter] != '\0'
		&& !is_special_char(str[iter]) && !ft_isspace(str[iter]))
		iter++;
	cmd = ft_substr(str, 0, iter + 1);
	if (is_a_valid_command(cmd, data))
	{
		save_command_so_far(data, cmd);
		command_iter++;
	}
	else
	{
		printf("minishell: %s: command not found\n", cmd);
		free(cmd);
		//free_stuff
	}
	return (iter);
}

int	read_argument(t_data *data, char *str)
{
	int iter;

	iter = 0;
	while (str[iter] != '\0')
	{
		if (str[iter] == '\'' || str[iter] == '\"')
			iter += handle_quote(data, str + iter); //advance until closing quote. dont forget on this function to check which quote char it is
		else if (str[iter] == '$')
			iter += handle_dollar_sign(data, str); //this must finish on a space or special char
		else if (ft_isspace(str[iter]) || is_special_char(str[iter]))
		{
			save_new_argument_so_far(data, str, iter);
			break;
		}
		else
			iter++;
	}
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
