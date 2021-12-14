/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:55:56 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 19:56:51 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../main.h"
# include "__cd.h"
# include "__echo.h"
# include "__env.h"
# include "__exit.h"
# include "__export.h"
# include "__pwd.h"
# include "__unset.h"

typedef int	(*t_builtin)(char **args, int *ctx);

int			exec_builtin(t_leaf_node *leaf, int *ctx);

bool		is_builtin(char *cmd);

#endif // !BUILTINS_H