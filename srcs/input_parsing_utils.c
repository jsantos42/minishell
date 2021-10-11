#include "../headers/input_parsing_utils.h"

int	is_special_char(char chr)
{
	if (chr == '|' || chr == '&'|| chr == '\'' || chr == '\"'
		|| chr == '<' || chr == '>' || chr == '$' || chr == '\\' || chr == ';')
		return (1);
	else
		return (0);
}

int	advance_to_closing_quote(t_data *data, char *str)
{
	char	quote_type;
	int		iter;

	quote_type = *str;
	iter = -1;
	while (str[++iter] != '\0')
	{
		if (str[iter] == quote_type)
			return (iter);
	}
	terminate_program(UNCLOSED_QUOTES, data);
}
