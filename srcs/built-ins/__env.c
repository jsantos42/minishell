/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:51:01 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 16:54:05 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/built-ins/__env.h"

int	__env(char **args, int *ctx)
{
	t_list	*env_list;
	t_pair	*var;

	(void)args;
	(void)ctx;
	env_list = *(get_data(NULL)->env.list);
	while (env_list)
	{	
		var = ((t_pair *)env_list->content);
		if (var->value)
			printf("%s=%s\n", var->key, var->value);
		env_list = env_list->next;
	}
	return (1);
}
