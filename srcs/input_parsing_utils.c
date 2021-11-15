#include "../headers/input_parsing_utils.h"

bool	is_special_char(char chr)
{
	if (chr == '|' || chr == '&' || chr == '<' || chr == '>'
	|| chr == '\\' || chr == ';')
		return (true);
	else
		return (false);
}

bool	is_quote_char(char chr)
{
	return (chr == '\'' || chr == '\"');
}

bool	is_dollar_sign(char chr)
{
	return (chr == '$');
}


