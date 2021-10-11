#ifndef PARSER_H
# define PARSER_H

# include "main.h"

int	parse_input(t_data *data);
int	read_command(t_data *data, t_cmd *command, char **str);
int	read_argument(t_data *data, t_cmd *command, char **str);
void	save_new_argument(t_data *data, t_cmd *command, char **str, int end);

#endif