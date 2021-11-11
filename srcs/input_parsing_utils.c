#include "../headers/input_parsing_utils.h"

int	is_special_char(char chr)
{
	if (chr == '|' || chr == '&'|| chr == '\'' || chr == '\"'
		|| chr == '<' || chr == '>' || chr == '$' || chr == '\\' || chr == ';')
		return (1);
	else
		return (0);
}

/*
**	This makes sure nothing between quotes gets interpreted as a command. It
**	starts by defining which type of quote it's using and runs through the
**	string str. When it reaches the same quote char, as long as it wasn't
**	escaped, it returns the number of iterations made.
**
**	NOTE1: it starts checking on index 1 (since index 0 is the opening quote)
**	and, as such, it does not require a safety check for a negative index when
**	doing the operation str[iter - 1].
**	NOTE2: the return (0) line at the end of the function is actually redundant,
**	but the compiler does raise an error if it's not there.
*/

int	advance_to_closing_quote(char *str)
{
	char	quote_type;
	int		iter;

	quote_type = *str;
	iter = 0;
	while (str[++iter] != '\0')
	{
		if (str[iter] == quote_type && str[iter - 1] != '\\')
			return (iter);
	}
	terminate_program(UNCLOSED_QUOTES);
	return (0);
}
