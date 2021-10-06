#ifndef PARSER_H
# define PARSER_H

# include "main.h"

void	parse_input(t_data *data);
int	handle_white_space(char *input);
int	handle_pipe(char *input);
int	handle_redirection(char *input);

#endif