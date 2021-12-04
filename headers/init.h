#ifndef INIT_H
# define INIT_H

# include "main.h"

void	init_data(t_data *data, int argc, char **argv, char **envp);
t_tree	*init_leaf_node(t_tree *previous);
t_tree	*init_branch_node(t_tree *previous);
void	init_signals(t_data *data);

#endif