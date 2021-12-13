/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:42:56 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:43:32 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser/special_chars.h"

bool	is_special_char(char chr)
{
	return (chr == '|' || chr == '&' || chr == '<' || chr == '>');
}

void	handle_pipe(t_tree **current_node, char *str, int *i)
{
	int	operator;

	operator = PIPE;
	if (str[++(*i)] == '|')
	{
		operator = OR;
		(*i)++;
	}
	relink(current_node, operator);
}

void	handle_amper(t_tree **current_node, t_data *data, char *str, int *i)
{
	int	operator;

	operator = 0;
	if (str[++(*i)] == '&')
	{
		operator = AND;
		(*i)++;
	}
	else
		data->forbidden_chars = true;
	relink(current_node, operator);
}
