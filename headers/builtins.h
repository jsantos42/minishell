#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

typedef int	(*ft_builtin)(char **args, int *ctx);

int	exec_builtin(t_leaf_node *leaf, int *ctx);

bool	is_builtin(char *cmd);

int	__echo(char **args, int *ctx);

int	__cd(char **args, int *ctx);

int	__pwd(char **args, int *ctx);

int	__export(char **args, int *ctx);

int	__unset(char **args, int *ctx);

int	__env(char **args, int *ctx);

int	__exit(char **args, int *ctx);

#endif // !BUILTINS_H