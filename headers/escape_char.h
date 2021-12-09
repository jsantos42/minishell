#ifndef ESCAPE_CHAR_H
# define ESCAPE_CHAR_H

# include "main.h"

#define ESCAPECHAR 1

bool	is_escape_char(char chr);
bool	is_escaped(char *str, int i);
int		remove_escape_char(t_data *data, int *escaped_char);

#endif
