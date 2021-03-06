/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:43:07 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:43:32 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser/special_chars_utils.h"

///this function needs renaming
/*
 * create new branch node
 * (*current_node)->previous->branch.right = branch_node;
 * branch_node->left = *current_node
 * *current_node = branch_node->right;
 */
void	relink(t_tree **current_node, int operator)
{
	t_data	*data;
	t_tree	*branch_node;
	t_tree	*new_leaf_node;

	data = get_data(NULL);
	branch_node = init_branch_node((*current_node)->previous);
	new_leaf_node = init_leaf_node(branch_node);
	if ((*current_node)->previous)
		(*current_node)->previous->branch.right = branch_node;
	else
		data->tree = branch_node;
	(*current_node)->previous = branch_node;
	branch_node->branch.left = *current_node;
	branch_node->branch.right = new_leaf_node;
	branch_node->branch.operator = operator;
	*current_node = branch_node->branch.right;
}
