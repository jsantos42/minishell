/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:39:19 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:43:31 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/init.h"

void	init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->tree = NULL;
	data->forbidden_chars = false;
	data->escaped = false;
	data->sigint_received = false;
	data->stdin_fd = 0;
	data->env = ft_init_env(envp);
	data->status = 0;
	data->plist = NULL;
	get_data(data);
	init_signals();
}

t_tree	*init_leaf_node(t_tree *previous)
{
	t_tree	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		terminate_program("", MALLOC);
	new_node->type = LEAF_NODE;
	new_node->leaf.args = NULL;
	new_node->leaf.nb_args = 0;
	new_node->leaf.redir_input = NULL;
	new_node->leaf.redir_output = NULL;
	new_node->leaf.append_mode = false;
	new_node->leaf.here_doc = false;
	new_node->leaf.heredoc_file = NULL;
	new_node->leaf.delimiter = NULL;
	new_node->previous = previous;
	return (new_node);
}

t_tree	*init_branch_node(t_tree *previous)
{
	t_tree	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		terminate_program("", MALLOC);
	new_node->type = BRANCH_NODE;
	new_node->branch.operator = 0;
	new_node->branch.left = NULL;
	new_node->branch.right = NULL;
	new_node->previous = previous;
	return (new_node);
}

void	init_history(void)
{
	if (access(".history", F_OK) == 0)
		read_history(".history");
	else
	{
		open(".history", O_CREAT | O_APPEND | O_WRONLY, 0644);
		read_history(".history");
	}
}
