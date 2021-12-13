/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:42:09 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:43:31 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser/redirect_output.h"

void	handle_output_redirection(t_tree **current_node, t_data *data, int *i)
{
	char	*redir;

	(*i)++;
	if (data->input[*i] == '>')
	{
		(*current_node)->leaf.append_mode = true;
		(*i)++;
	}
	skip_white_space(data->input, i);
	redir = parser_core(data, i, true);
	(*current_node)->leaf.redir_output = redir;
}
