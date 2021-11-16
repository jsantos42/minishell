#ifndef PARSER_H
# define PARSER_H

# include "main.h"

int	parse_input(t_data *data);
int	read_cmd_and_args(t_data *data, t_leaf_node *current_node, char **str);
int	read_argument(t_leaf_node *current_node, char **str);
void	save_new_argument(t_leaf_node *current_node, char *new_arg);

#endif