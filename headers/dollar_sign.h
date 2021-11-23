#ifndef DOLLAR_SIGN_H
#define DOLLAR_SIGN_H

# include "main.h"
# define  DOLLAR_SIGN 1

bool	is_dollar_sign(char chr);
void	handle_dollar_sign(t_data *data, int dollar_pos);
int		get_var_length(char *var);
char	*replace_input(char *original, char *expanded, int dollar_pos, size_t name_len);

#endif