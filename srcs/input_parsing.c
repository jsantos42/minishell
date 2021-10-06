#include "../headers/input_parsing.h"

/* alternative: locate the special chars from the start
 if '>' or '<', next is file_name
else is always command

if ('|'), it means new command

 in https://unix.stackexchange.com/questions/86247/what-does-ampersand-mean-at-the-end-of-a-shell-script-line
A && B means "run command B if command A succeeded", and A || B means "run command B if command A failed".
 Examples: 'cd tmp && ls' will run ls only if folder tmp exists. Or in a script: 'cd foobar || exit 10' will stop the
 execution (exit) if folder foobar doesnt' exist. –

 */
void	parse_input(t_data *data)
{
	char *str;

	str = data->input;
	str += handle_white_space(str);
	while (*str != '\0')
	{
		/*
		 * find location of first | and &
		 * then check if there are quotes and if their location surrounds the found pipe/ampersand
		 * 		make sure to check for both quotes types
		 * 		if no closing quotes, error (unless surrounded by quotes of the other type)
		 * if yes, ignore found |or& and find next one
		 * otherwise, read command until then
		 * then check next char to see if this was actually a pipe or a || sign
		 */

		while (*str != '|') //missing the quotes and the && and ||
			read_command();
		command++;
	}
}


void read_command()
{
	while (*str != '\0')
	{
		reading_command = true;
		if (*str != '<' || *str != '<')
		{
			reading_command = false;
			read_arguments; //until isspace==true
		}


	}
}

	/*old version

		if (*str == '\\' || *str == ';')
			terminate_program(SPECIAL_CHAR, data);
		else if (*str == '\'' || *str == '\"')
			str += save_quoted_str(data, str); //dont forget on this function to check which quote char it is
		else if (*str == '$')
			str += expand_var(data, str);
		else if (ft_isspace(*str))
		{
			command++; //the previous command terminated, start recording next one
			str += handle_white_space(str);
		}
		else if (*str == '|')
		{
			command++; //the previous command terminated, start recording next one
			str += handle_pipe(data, str);
			//check for next char to be different than pipe, to avoid OR op
			//save operation pipe
		}
		else if (*str == '<' || *str == '>')
		{
			command++; //the previous command terminated, start recording next one
			str += handle_redirection(data, str);
			//check for next char to be different than this one
			//save operation
		}
		else
			append_to_cmd(data, str++); //save_command_so_far; //ft_add_chars(data->commands[x], *str, 1); //with strjoin (do I need to free the original? check)
			*/


int	move_beyond_white_space(char *input)
{
	int	iter;

	iter = -1;
	while (input[++iter] != '\0')
	{
		if (ft_isspace(input[iter]))
			iter++;
		else
			break ;
	}
	return (iter);
}

if (save_quoted_str(input) < 0)
//look for other corresponding quote and save str in between
