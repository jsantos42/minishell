#ifndef QUOTE_CHAR_H
# define QUOTE_CHAR_H

# include "main.h"

# define PAIR_OF_QUOTES 2

bool	is_quote_char(char chr);
char	*handle_quote_char(char *input, int *quote_pos);

#endif