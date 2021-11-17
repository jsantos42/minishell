#ifndef SPECIAL_CHARS_H
# define SPECIAL_CHARS_H

# include "main.h"

bool	is_special_char(char chr);
void	handle_pipe(t_tree **current_node, char **str);
void	handle_amper(t_tree **current_node, char **str);
void	handle_input_redirection(t_tree **current_node, char **str);
void	handle_output_redirection(t_tree **current_node, char **str);

#endif