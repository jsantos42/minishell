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

/*
**	Note: on heredoc, bash does not interpret the '$' as a variable expansion,
**	that's why this function only calls handle_dollar_sign when it's not on
**	here_doc mode.
*/

void	handle_input_redirection(t_tree **current_node, char **str)
{
	int	i;

	(*str)++;
	if (**str == '<')
	{
		(*current_node)->leaf.here_doc = true;
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
		else if (is_dollar_sign((*str)[i]) && !(*current_node)->leaf.here_doc)
			*str = handle_dollar_sign(*str, &i);
	}
	if (i != 0 && (*current_node)->leaf.here_doc == false)
		(*current_node)->leaf.redir_input = ft_substr(*str, 0, i);
	else if (i != 0 && (*current_node)->leaf.here_doc == true)
		(*current_node)->leaf.delimiter = ft_substr(*str, 0, i);
	*str += i;
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
