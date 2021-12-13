/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:33:27 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 20:38:49 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executor/exec_utils.h"

#define INPUT 0
#define OUTPUT 1

char	*get_cmd_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	if (!ft_strchr(cmd, '/'))
	{
		i = 0;
		paths = ft_split(get_env_var("PATH"), ':', NULL);
		while (paths[i])
		{
			path = ft_strnjoin(3, paths[i], "/", cmd);
			if (access(path, X_OK) == 0)
				return (path);
			free(paths[i]);
			free(path);
			i++;
		}
	}
	else if (access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

void	open_io_files(t_leaf_node *leaf, int *ctx)
{
	const char	*redir_in = leaf->redir_input;
	const char	*redir_out = leaf->redir_output;
	const bool	append_mode = leaf->append_mode;
	const bool	here_doc = leaf->here_doc;

	if (redir_in)
	{
		ctx[INPUT] = open(redir_in, O_RDONLY, 0);
		if (ctx[INPUT] == -1)
			printf("Minishell: no such file or directory: %s\n", redir_in);
	}
	if (redir_out && append_mode)
		ctx[OUTPUT] = open(redir_out, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (redir_out)
		ctx[OUTPUT] = open(redir_out, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (here_doc)
		ctx[INPUT] = run_heredoc(leaf);
}

void	ft_close_fds(t_leaf_node *leaf, int *ctx)
{
	if (ctx[INPUT] != STDIN_FILENO)
		close(ctx[INPUT]);
	if (ctx[OUTPUT] != STDOUT_FILENO)
		close(ctx[OUTPUT]);
	if (leaf->heredoc_file)
		unlink(leaf->heredoc_file);
}
