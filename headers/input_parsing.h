#ifndef PARSER_H
# define PARSER_H

# include "main.h"

void	parse_input(t_data *data);
int	read_command(t_data *data, char *str);
int	read_argument(t_data *data, char *str);

#endif