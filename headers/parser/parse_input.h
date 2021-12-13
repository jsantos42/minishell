/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:34 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:48:19 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INPUT_H
# define PARSE_INPUT_H

# include "../main.h"

# define NEW_ARG	1
# define NULLTERM	1

int		parse_input(t_data *data);
void	read_cmd_and_args(t_data *data, t_leaf_node *current_node, int *i);
char	*parser_core(t_data *data, int *i, bool interpret_dollar);

#endif
