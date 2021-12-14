/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:46:02 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 19:46:03 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../main.h"

t_pair	*build_var_pair(char *envp_var);

t_env	ft_init_env(char **envp);

bool	is_env_var(t_list *env_list, char *key);

void	print_env_vars(t_env *env, int *ctx);

#endif