#include "../headers/input_parsing_utils.h"

int	is_special_char(char chr)
{
	if (chr == '|' || chr == '&'|| chr == '\'' || chr == '\"'
		|| chr == '<' || chr == '>' || chr == '$' || chr == '\\' || chr == ';')
		return (1);
	else
		return (0);
}
