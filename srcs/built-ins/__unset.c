/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:50:50 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 16:50:51 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/built-ins/__unset.h"

int	__unset(char **args, int *ctx)
{
	t_list	*env_list;
	t_list	*env_list_prev;
	t_pair	*var;
	int		iter;

	(void)ctx;
	env_list_prev = NULL;
	env_list = *(get_data(NULL)->env.list);
	iter = 0;
	while (env_list)
	{	
		var = ((t_pair *)env_list->content);
		if (!ft_strncmp(var->key, args[1], ft_strlen(var->key) + 1))
		{
			env_list_prev->next = env_list->next;
			ft_lstdelone(env_list, del_env_var);
			ft_matrix_del_one(get_data(NULL)->env.array, iter);
			get_data(NULL)->env.nb_vars--;
			return (0);
		}
		env_list_prev = env_list;
		env_list = env_list->next;
		iter++;
	}
	return (1);
}
