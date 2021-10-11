#ifndef INPUT_PARSING_UTILS_H
# define INPUT_PARSING_UTILS_H

# include "main.h"

int	is_special_char(char chr);
int	advance_to_closing_quote(t_data *data, char *str);

#endif