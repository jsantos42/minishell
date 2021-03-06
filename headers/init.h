/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:19 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:48:19 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "main.h"

void	init_data(t_data *data, char **envp);
t_tree	*init_leaf_node(t_tree *previous);
t_tree	*init_branch_node(t_tree *previous);
void	init_history(void);

#endif
