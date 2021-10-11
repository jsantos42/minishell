#ifndef HANDLE_SPECIAL_CHARS_H
# define HANDLE_SPECIAL_CHARS_H

# include "main.h"

int	handle_white_space(char *input);
int	handle_dollar_sign(t_data *data, char **str);
void	handle_pipe(t_data *data, char **str);
void	handle_amper(t_data *data, char **str);
void	handle_redirection(t_data *data, char **str);

#endif