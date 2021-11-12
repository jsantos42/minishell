#ifndef INPUT_PARSING_UTILS_H
# define INPUT_PARSING_UTILS_H

# include "main.h"

bool	is_special_char(char chr);
bool	is_quote_char(char chr);
bool	is_dollar_char(char chr);
int	advance_to_closing_quote(char *str);

#endif