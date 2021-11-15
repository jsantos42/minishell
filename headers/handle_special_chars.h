#ifndef HANDLE_SPECIAL_CHARS_H
# define HANDLE_SPECIAL_CHARS_H

# include "main.h"

# define PAIR_OF_QUOTES 2

int	skip_white_space(char *input);
char	*handle_dollar_sign(char *input, int *dollar_pos);
void	handle_input_redirection(t_tree **current_node, char **str);
void	handle_output_redirection(t_tree **current_node, char **str);

		void	handle_pipe(t_tree **current_node, char **str);
void	handle_amper(t_tree **current_node, char **str);
void	relink(t_tree **current_node, int operator);
char	*handle_quote_char(char *input, int *quote_pos);

#endif