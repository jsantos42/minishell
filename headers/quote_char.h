#ifndef QUOTE_CHAR_H
# define QUOTE_CHAR_H

# include "main.h"

# define QUOTE_CHAR 1

bool	is_quote_char(char chr);
void	handle_quote_char(t_data *data, int *quote_pos);
void	look_for_expansions(t_data *data, int i, int end);

#endif