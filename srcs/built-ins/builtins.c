/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:51:08 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/14 17:20:55 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/built-ins/builtins.h"

#define PIPELINE 2
#define TRUE 1
#define FALSE 0

bool	is_builtin(char *cmd)
{
	const char			*keys[8] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int					size;
	int					i;

	size = ft_strlen(cmd);
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd, keys[i], size + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_leaf_node *leaf, int *ctx)
{
	const char			*keys[8] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	const t_builtin		builtin[8] = {
		__echo, __cd, __pwd, __export, __unset, __env, __exit, NULL};
	int					cmd;
	int					ret;

	cmd = -1;
	while (keys[++cmd])
		if (!ft_strncmp(keys[cmd], leaf->args[0], ft_strlen(keys[cmd]) + 1))
			ret = builtin[cmd](leaf->args, ctx);
	if (ctx[PIPELINE] == TRUE)
		exit(ret);
	return (ret);
}
