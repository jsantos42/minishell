#ifndef QUOTE_CHAR_H
# define QUOTE_CHAR_H

# include "main.h"

# define QUOTE_CHAR 1

bool	is_quote_char(char chr);
void	handle_quote_char(t_data *data, int *quote_pos);
int		get_closing_quote(t_data *data, int i);
void	look_for_expansions(t_data *data, int i, int *end);
char	*remove_quotes(t_data *data, int *opening_quote, int closing_quote);

#endif