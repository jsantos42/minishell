/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_and_free.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:54:59 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/14 14:55:09 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINATE_AND_FREE_H
# define TERMINATE_AND_FREE_H

# include "main.h"

void	terminate_program(char *name, int error);
void	free_data(void);
void	*free_tree(t_tree *tree);
int		print_input_error(void);
void	*xmalloc(size_t size, char *file, int line);

#endif
