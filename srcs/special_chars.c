#include "../headers/special_chars.h"

bool	is_special_char(char chr)
{
	if (chr == '|' || chr == '&' || chr == '<' || chr == '>')
		return (true);
	else
		return (false);
}

void	handle_pipe(t_tree **current_node, char *str, int *i)
{
	int	operator;

	operator = PIPE;
	if (str[++*i] == '|')
	{
		operator = OR;
		(*i)++;
	}
	relink(current_node, operator);
}

void	handle_amper(t_tree **current_node, char *str, int *i)
{
	int	operator;

	operator = 0;
	if (str[++*i] == '&')
	{
		operator = AND;
		(*i)++;
	}
	else
		terminate_program("", RUN_BG);
	relink(current_node, operator);
}
