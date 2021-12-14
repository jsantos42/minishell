/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_accessors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:03:45 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 20:54:05 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/env/env_accessors.h"

int	update_env_var(char *key, char *new_value)
{
	t_list	*env_list;
	char	**env_array;
	t_pair	*var;

	env_list = *(get_data(NULL)->env.list);
	env_array = get_data(NULL)->env.array;
	while (env_list)
	{
		var = ((t_pair *)env_list->content);
		if ((!ft_strncmp(var->key, key, ft_strlen(key) + 1)) && new_value)
		{
			free(*env_array);
			*env_array = ft_strnjoin(3, key, "=", new_value);
			if (var->value)
				free(var->value);
			var->value = ft_strdup(new_value);
			return (0);
		}
		env_list = env_list->next;
		env_array++;
	}
	return (1);
}

char	*get_env_var(char *key)
{
	t_list	*env_list;
	t_pair	*var;

	env_list = *(get_data(NULL)->env.list);
	while (env_list)
	{
		var = ((t_pair *)env_list->content);
		if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
			return (var->value);
		env_list = env_list->next;
	}
	return (NULL);
}

void	del_env_var(void *env_var_void)
{
	t_pair	*env_var;

	env_var = (t_pair *)env_var_void;
	if (env_var)
	{
		if (env_var->key)
			free(env_var->key);
		if (env_var->value)
			free(env_var->value);
		free(env_var);
	}
}
