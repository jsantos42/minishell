/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_char.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:45:53 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:48:19 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESCAPE_CHAR_H
# define ESCAPE_CHAR_H

# include "../main.h"

# define ESCAPECHAR 1

bool	is_escape_char(char chr);
bool	is_escaped(char *str, int i);
int		remove_escape_char(t_data *data, int *escaped_char);
int		escape(t_data *data, int *i);

#endif
