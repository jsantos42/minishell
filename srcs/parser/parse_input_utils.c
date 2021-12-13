/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:39:49 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:43:31 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser/parse_input_utils.h"

/*
**	The input is white-space insensitive, so the program can skip white space.
*/

void	skip_white_space(char *input, int *i)
{
	while (input[*i] != '\0' && ft_isspace(input[*i]))
		(*i)++;
}

/*
**	Creates a new_matrix, allocating enough memory to contain both the previous
**	allocated argument strings* and the new argument. Frees the previous
**	allocated matrix* and makes the current_node->args point to this new_matrix.
**	Finally, it increases the number of arguments (note that this nb_args
**	includes the command itself, which should be the first arg).
**
**	*in case it's not the first time it's called.
*/

void	save_new_argument(t_leaf_node *current_node, char *new_arg)
{
	char	**new_matrix;
	int		i;
	size_t	size;

	size = current_node->nb_args + NEW_ARG + NULLTERM;
	new_matrix = NULL;
	new_matrix = malloc(size * sizeof(char *));
	if (!new_matrix)
		terminate_program("", MALLOC);
	i = -1;
	while (++i < current_node->nb_args)
		new_matrix[i] = current_node->args[i];
	new_matrix[i] = new_arg;
	new_matrix[++i] = NULL;
	free_if_not_null(current_node->args);
	current_node->args = new_matrix;
	current_node->nb_args++;
}
