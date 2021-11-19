#ifndef SPECIAL_CHARS_H
# define SPECIAL_CHARS_H

# include "main.h"

bool	is_special_char(char chr);
void	handle_pipe(t_tree **current_node, char *str, int *i);
void	handle_amper(t_tree **current_node, char *str, int *i);
void	handle_input_redirection(t_tree **current_node, char **str, int *i);
void	handle_output_redirection(t_tree **current_node, char **str, int *i);

#endif