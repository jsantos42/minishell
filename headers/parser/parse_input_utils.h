/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:56 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:48:20 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INPUT_UTILS_H
# define PARSE_INPUT_UTILS_H

# include "../main.h"

void	skip_white_space(char *input, int *i);
void	save_new_argument(t_leaf_node *current_node, char *new_arg);

#endif
