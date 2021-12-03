#include "../headers/parse_input_utils.h"

void	skip_white_space(char *input, int *i)
{
	while (input[*i] != '\0' && ft_isspace(input[*i]))
		(*i)++;
}

char	*check_for_nl_char(char *input, int *i)
{
	char	*new_input;

	new_input = NULL;
	if (*i > 0 && is_escaped(input, *i - 1))
		new_input = remove_escape_char(input, i);
	else
		terminate_program(SPECIAL_CHAR);
	return (new_input);
}
