/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_and_free.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:48:03 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:48:21 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_UTILS_H
# define ERROR_UTILS_H

# include "main.h"

void	terminate_program(char *name, int error);
void	free_data(void);
void	*free_tree(t_tree *tree);
int		print_input_error(void);

#endif
