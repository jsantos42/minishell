#include "../headers/input_parsing.h"

void	parse_input(t_data *data)
{
	char *str;

	str = data->input;
	str += handle_white_space(str);
	// alternative: locate the special chars from the start
	while (*str != '\0')
	{
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
		}
	}
}


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
