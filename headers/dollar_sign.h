#ifndef DOLLAR_SIGN_H
#define DOLLAR_SIGN_H

# include "main.h"
# define  DOLLAR_SIGN 1

typedef	struct s_dollar {
	char	*name;
	char	*expanded;
	size_t	name_len;
	size_t	expanded_len;
}	t_dollar;

bool	is_dollar_sign(char chr);
void	handle_dollar_sign(t_data *data, int dollar_pos);
int		get_var_length(char *var);
char	*replace_input(char *original, t_dollar *dollar, int dollar_pos);

#endif