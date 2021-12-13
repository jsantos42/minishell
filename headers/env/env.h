#ifndef ENV_H
# define ENV_H

# include "../main.h"

t_pair	*build_var_pair(char *envp_var);
t_env	ft_init_env(char **envp);
bool	is_env_var(t_list *env_list, char *key);
void	print_env_vars(t_env *env, int *ctx);
int		update_env_var(char *key, char *new_value);
char	*get_env_var(char *key);
void	del_env_var(void *env_var_void);

#endif