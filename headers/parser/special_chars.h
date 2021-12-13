/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:47:39 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:48:20 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECIAL_CHARS_H
# define SPECIAL_CHARS_H

# include "../main.h"

bool	is_special_char(char chr);
void	handle_pipe(t_tree **current_node, t_data *data, char *str, int *i);
void	handle_amper(t_tree **current_node, t_data *data, char *str, int *i);

#endif
