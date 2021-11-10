#include "../headers/handle_special_chars.h"

int	skip_white_space(char *input)
{
	int	iter;

	iter = -1;
	while (input[++iter] != '\0')
	{
		if (!ft_isspace(input[iter]))
			break ;
	}
	return (iter);
}

int	handle_dollar_sign(t_data *data, char **str)
{
	//this must finish on a space or special char
	(void)data;
	(void)str;
	return (0);
}

void	handle_pipe(t_data *data, t_cmd **command, char **str)
{
	t_cmd	*new_command;

	if (**str == *(*str + 1))
	{
		(*command)->operator = OR;
		(*str) += 2;
	}
	else
	{
		(*command)->operator = PIPE;
		(*str)++;
	}
	new_command = NULL;
	init_command(data, &new_command);
	(*command)->right = new_command;
	*command = (*command)->right;
}

void	handle_amper(t_data *data, t_cmd **command, char **str)
{
	t_cmd	*new_command;

	if (**str == *(*str + 1))
	{
		(*command)->operator = AND;
		(*str) += 2;
	}
	else
		terminate_program(RUN_BG, data);
	new_command = NULL;
	init_command(data, &new_command);
	(*command)->right = new_command;
	*command = (*command)->right;
}

void	handle_redirection(t_data *data, char **str)
{
	(void)data;
	(void)str;
	//check for next char to be different than this one
	//save operation

}
