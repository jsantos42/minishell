/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:50:48 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/14 17:10:24 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/built-ins/__export.h"

int	__export(char **args, int *ctx)
{
	t_pair	*pair;
	t_data	*data;
	int		iter;

	data = get_data(NULL);
	if (!args[1])
	{
		print_env_vars(&data->env, ctx);
		return (0);
	}
	iter = 0;
	while (args[++iter])
	{
		pair = build_var_pair(args[iter]);
		if (is_env_var(*(data->env.list), pair->key))
			update_env_var(pair->key, pair->value);
		else
		{
			ft_lstadd_back(data->env.list, ft_lstnew(pair));
			data->env.array = ft_push_to_matrix(data->env.array, args[iter]);
			data->env.nb_vars++;
		}
	}
	return (0);
}
