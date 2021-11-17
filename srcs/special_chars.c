#include "../headers/special_chars.h"

bool	is_special_char(char chr)
{
	if (chr == '|' || chr == '&' || chr == '<' || chr == '>'
		|| chr == '\\' || chr == ';')
		return (true);
	else
		return (false);
}

void	handle_pipe(t_tree **current_node, char **str)
{
	int	operator;

	operator = PIPE;
	(*str)++;
	if (**str == '|')
	{
		operator = OR;
		(*str)++;
	}
	relink(current_node, operator);
}

void	handle_amper(t_tree **current_node, char **str)
{
	int	operator;

	operator = 0;
	(*str)++;
	if (**str == '&')
	{
		operator = AND;
		(*str)++;
	}
	else
		terminate_program(RUN_BG);
	relink(current_node, operator);
}

/// has to output error when the next char is a PIPE or an AMPERSAND or a third >>>

void	handle_input_redirection(t_tree **current_node, char **str)
{
	(void)current_node;
	(void)str;
//	(*str++);
//	if
//
//	(void)str;
//	//check for next char to be different than this one
//	//save operation

}



void	handle_output_redirection(t_tree **current_node, char **str)
{
	int	i;

	(*str)++;
	if (**str == '>')
	{
		(*current_node)->leaf.append_mode = true;
		(*str)++;
	}
	*str += skip_white_space(*str);
	i = -1;
	while ((*str)[++i] != '\0'
		   && !is_special_char((*str)[i])
		   && !ft_isspace((*str)[i]))
	{
		if (is_quote_char((*str)[i]))
			*str = handle_quote_char(*str, &i);
		else if (is_dollar_sign((*str)[i]))
			*str = handle_dollar_sign(*str, &i);
	}
	if (i != 0)
		(*current_node)->leaf.redir_output = ft_substr(*str, 0, i);
	*str += i;
}










