#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

void	exec_builtin(t_leaf_node *leaf, int *ctx);

bool	is_builtin(char *cmd);

void	builtin_echo(char **args, int *ctx);

void	builtin_cd(char **args);

void	builtin_env(int *ctx);

void	builtin_export(t_data *data, char **args, int *ctx);

void	print_env_vars(t_list *env, int *ctx);

void	builtin_exit(void);

#endif // !BUILTINS_H