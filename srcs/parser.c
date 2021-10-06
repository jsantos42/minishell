#include "../headers/parser.h"

int	move_beyond_white_space(char *input);

int	parse_input(t_data *data)
{
	char	*str;

	str = data->input;
	str += move_beyond_white_space(str);
	while (*str != '\0')
	{
		if (*str == '\\' || *str == ';')
			handle_error(SPECIAL_CHAR);
		else if (*str == '\'' || *str == '\"')
			str += save_quoted_str(str); //dont forget on this function to check which quote char it is
		else if (*str == '$')
			str += expand_var;
		else
		{
			save_command_so_far; //with strjoin (do I need to free the original? check)
			if (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' || *str == '\r')
			{
				command++; //the previous command terminated, start recording next one
				str += move_beyond_white_space(str);
			}
			else if (*str == '|')
			{
				command++; //the previous command terminated, start recording next one
				//check for next char to be different than pipe, to avoid OR op
				//save operation pipe
			}
			else if (*str == '<' || *str == '>')
			{
				command++; //the previous command terminated, start recording next one
				//check for next char to be different than this one
				//save operation
			}
			else
				str++;
		}
	}
	if (is_exit_command(data.input))
		break ;
	if (is_a_valid_command(&data))
		execute_command(&data);
	else
		printf("%s: command not found\n", data.input);
}

int	move_beyond_white_space(char *input)
{
	int	iter;

	iter = -1;
	while (input[++iter] != '\0')
	{
		if (input[iter] == ' '
		   || input[iter] == '\t'
		   || input[iter] == '\n'
		   || input[iter] == '\v'
		   || input[iter] == '\f'
		   || input[iter] == '\r')
			iter++;
		else
			break ;
	}
	return (iter);
}

if (save_quoted_str(input) < 0)
//look for other corresponding quote and save str in between
