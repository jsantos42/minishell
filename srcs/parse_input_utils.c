#include "../headers/parse_input_utils.h"

void	skip_white_space(char *input, int *i)
{
	while (input[*i] != '\0' && ft_isspace(input[*i]))
		(*i)++;
}
