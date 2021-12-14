/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_and_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:43:21 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 20:44:14 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/terminate_and_free.h"

void	terminate_program(char *name, int error)
{
	free_data();
	printf("ERROR\n");
	if (error == MALLOC)
		printf("Memory allocation failed.\n");
	else if (error == DUP2)
		printf("%s: Error copying file descriptors\n", name);
	else if (error == CMD_NOT_FOUND)
		printf("%s: command not found\n", name);
	exit(error);
}

void	free_data(void)
{
	t_data	*data;

	data = get_data(NULL);
	data->input = free_if_not_null(data->input);
	data->tree = free_tree(data->tree);
	ft_lstclear(&data->plist, free);
}

int	print_input_error(void)
{
	printf("INPUT ERROR\nThis shell does not support the following chars:\n");
	printf("  Semicommas and parenthesis between commands\n");
	printf("  New-line char\n");
	printf("  Unclosed quotes\n");
	printf("  Run_in_background char\n");
	printf("  AND and OR operands (&& ||)\n\n");
	return (0);
}

void	*free_tree(t_tree *tree)
{
	if (tree)
	{
		if (tree->type == LEAF_NODE)
		{
			free_matrix((void **)tree->leaf.args, tree->leaf.nb_args);
			tree->leaf.args = NULL;
			tree->leaf.redir_input = free_if_not_null(tree->leaf.redir_input);
			tree->leaf.redir_output = free_if_not_null(tree->leaf.redir_output);
			tree->leaf.heredoc_file = free_if_not_null(tree->leaf.heredoc_file);
			tree->leaf.delimiter = free_if_not_null(tree->leaf.delimiter);
		}
		else if (tree->type == BRANCH_NODE)
		{
			free_tree(tree->branch.left);
			free_tree((tree->branch.right));
		}
		free(tree);
	}
	return (NULL);
}

void	*xmalloc(size_t size, char *file, int line)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (ptr == NULL)
	{
		perror(file);
		perror("_");
		perror(ft_itoa(line));
		perror(" : Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
