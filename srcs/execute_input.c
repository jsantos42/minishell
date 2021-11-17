#include "../headers/execute_input.h"

#define READ_END 0
#define WRITE_END 1

static void	execute_node(t_tree *node, t_ctx *ctx);
static int	execute_leaf(t_leaf_node *leaf, t_ctx *ctx);
static int	execute_branch(t_branch_node *branch, t_ctx *ctx);
static char	*get_cmd_path(char *cmd, char **paths);

void	execute_input(t_data *data)
{
	t_ctx	ctx;

	ctx.fd_io[0] = STDIN_FILENO;
	ctx.fd_io[1] = STDOUT_FILENO;
	ctx.fd_close = -1;
	execute_node(data->tree, &ctx);
	while (data->active_proc--)
		wait(NULL);
	// waits gona be here;
	// wait while data->active_proc;
}

static void	execute_node(t_tree *node, t_ctx *ctx)
{
	if (node->type == LEAF_NODE)
		execute_leaf(&node->leaf, ctx);
	else if (node->type == BRANCH_NODE)
		execute_branch(&node->branch, ctx);
}

static int	execute_leaf(t_leaf_node *leaf, t_ctx *ctx)
{
	char	*cmd_path;
	int		p_id;
	t_data	*data;

	data = get_data(NULL);
	cmd_path = get_cmd_path(leaf->args[0], data->paths);
	if (!cmd_path)
		return (-1);
	
	p_id = fork();
	if (p_id == 0)
	{
		dup2(ctx->fd_io[0], STDIN_FILENO);
		dup2(ctx->fd_io[1], STDOUT_FILENO);
		//dprintf(2, "CMD: %s;   FD_IN: %d,   FD_OUT: %d\n", leaf->args[0], ctx->fd_io[0], ctx->fd_io[1]);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		execve(cmd_path, leaf->args, data->envp);
	}
	data->active_proc++;
	return (p_id);
}

static int	execute_branch(t_branch_node *branch, t_ctx *ctx)
{
	int		p[2];
	t_ctx	left_ctx;
	t_ctx	right_ctx;

	pipe(p);

	left_ctx = *ctx;
	left_ctx.fd_io[1] = p[WRITE_END];
	left_ctx.fd_close = p[READ_END];
	execute_node(branch->left, &left_ctx);

	right_ctx = *ctx;
	right_ctx.fd_io[0] = p[READ_END];
	right_ctx.fd_close = p[WRITE_END];
	execute_node(branch->right, &right_ctx);
	
	close(p[WRITE_END]);
	close(p[READ_END]);
	return (0);
}


static char	*get_cmd_path(char *cmd, char **paths)
{
	char	*part_path;
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{ 
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
