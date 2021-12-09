#ifndef PARSE_INPUT_UTILS_H
# define PARSE_INPUT_UTILS_H

# include "main.h"

void	skip_white_space(char *input, int *i);
char	*parser_core(t_data *data, int *i);

#endif