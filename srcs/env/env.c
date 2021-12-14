/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:03:34 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 17:11:23 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/env/env.h"

t_env	ft_init_env(char **envp)
{
	int		iter;
	t_pair	*env_var;
	t_env	env;

	env.nb_vars = -1;
	while (envp[++env.nb_vars])
		;
	env.array = xmalloc(sizeof(char *) * (env.nb_vars + 1), __FILE__, __LINE__);
	env.list = xmalloc(sizeof(t_list *), __FILE__, __LINE__);
	*env.list = NULL;
	iter = -1;
	while (envp[++iter])
	{	
		env_var = build_var_pair(envp[iter]);
		ft_lstadd_back(env.list, ft_lstnew(env_var));
		env.array[iter] = ft_strdup(envp[iter]);
	}
	env.array[iter] = NULL;
	env.envp = envp;
	return (env);
}

t_pair	*build_var_pair(char *envp_var)
{
	t_pair	*var;
	char	**splitted;

	var = xmalloc(sizeof(t_pair), __FILE__, __LINE__);
	splitted = ft_split(envp_var, '=', NULL);
	var->key = splitted[0];
	var->value = splitted[1];
	free(splitted);
	return (var);
}

bool	is_env_var(t_list *env_list, char *key)
{
	t_pair	*var;

	while (env_list)
	{
		var = ((t_pair *)env_list->content);
		if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

void	print_env_vars(t_env *env, int *ctx)
{
	int		i;
	char	*tmp;
	char	**order;

	order = ft_matrix_dup(env->array, env->nb_vars);
	i = 0;
	while (order[i + 1])
	{
		if (ft_strncmp(order[i], order[i + 1], ft_strlen(order[i])) > 0)
		{
			tmp = order[i];
			order[i] = order[i + 1];
			order[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	i = -1;
	while (order[++i])
	{
		ft_putstr_fd("declare -x ", ctx[1]);
		ft_putstr_fd(order[i], ctx[1]);
		write(ctx[1], "\n", 1);
	}
	free(order);
}
