#include "../headers/handle_special_chars.h"

int	handle_white_space(char *input)
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

int	handle_dollar_sign(t_data *data, char **str)
{
	//this must finish on a space or special char
	(void)data;
	(void)str;
	return (0);
}

void	handle_pipe(t_data *data, char **str)
{
	(void)data;
	(void)str;
	//check for next char to be different than pipe, to see if is OR op
	//args[command_iter] = NULL;
	//break;

}

void	handle_amper(t_data *data, char **str)
{
	(void)data;
	(void)str;
	//check for next char to be different than amper, to see if is AND op
	//args[command_iter] = NULL;
	//break;

}

void	handle_redirection(t_data *data, char **str)
{
	(void)data;
	(void)str;
	//check for next char to be different than this one
	//save operation

}
