#ifndef QUOTE_CHAR_H
# define QUOTE_CHAR_H

# include "main.h"

# define PAIR_OF_QUOTES 2

bool	is_quote_char(char chr);
char	*handle_quote_char(char *input, int *quote_pos);
char	*look_for_expansions(char *str, int i);
char	*remove_escape_char(char *str, int esc_pos);

#endif