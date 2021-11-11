#ifndef HANDLE_SPECIAL_CHARS_H
# define HANDLE_SPECIAL_CHARS_H

# include "main.h"

int	skip_white_space(char *input);
int	handle_dollar_sign(t_data *data, char **str);
void	handle_redirection(t_data *data, char **str);

void	handle_pipe(t_tree **current_node, char **str);
void	handle_amper(t_tree **current_node, char **str);
void	relink(t_tree **current_node, int operator);

#endif