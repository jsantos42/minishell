#include "../headers/execute_input.h"

#define READ_END 0
#define WRITE_END 1

static void	execute_node(t_tree *node, t_ctx *ctx);
static void	execute_leaf(t_leaf_node *leaf, t_ctx *ctx);
static void	execute_branch(t_branch_node *branch, t_ctx *ctx);
static char	*get_cmd_path(char *cmd, char **paths);
static void	ft_close_fds(t_list *plist);

void	execute_input(t_data *data)
{
	static t_ctx ctx = {.fd_io[0] = 0, .fd_io[1] = 1, .fd_close = -1};
	size_t	iter;
	int		status;

	// The Recursion Summoner
	execute_node(data->tree, &ctx);
	
	// Block execution of the main process until all childrens have been closed
	iter = ft_lstsize(data->plist);
	while (iter--)
	{
		waitpid(((t_proc *)data->plist->content)->id, &status, 0);
		if (((t_proc *)data->plist->content)->fd_io[0] != STDIN_FILENO)
			close(((t_proc *)data->plist->content)->fd_io[0]);
		if (((t_proc *)data->plist->content)->fd_io[1] != STDOUT_FILENO)
			close(((t_proc *)data->plist->content)->fd_io[1]);
		data->plist = data->plist->next;
	}
	ft_lstclear(&data->plist, free);

	data->status = WEXITSTATUS(status);
}

static void	execute_node(t_tree *node, t_ctx *ctx)
{
	if (node->type == LEAF_NODE)
		execute_leaf(&node->leaf, ctx);
	else if (node->type == BRANCH_NODE)
		execute_branch(&node->branch, ctx);
}

static void	execute_leaf(t_leaf_node *leaf, t_ctx *ctx)
{
	char	*cmd_path;
	t_proc	*p_data;
	t_data	*data;

	data = get_data(NULL);

	/// TODO: Get command path at parsing time
	cmd_path = get_cmd_path(leaf->args[0], data->paths);

	p_data = malloc(sizeof(t_proc));
	if (!p_data)
		terminate_program(MALLOC);
	p_data->fd_io[0] = ctx->fd_io[0];
	p_data->fd_io[1] = ctx->fd_io[1];
	p_data->id = fork();

	if (p_data->id == 0)
	{
		if (dup2(ctx->fd_io[0], 0) == -1 || dup2(ctx->fd_io[1], 1) == -1)
			terminate_program(DUP2);
		ft_close_fds(data->plist);
		execve(cmd_path, leaf->args, data->envp);
	}
	// Push the generated child infos to the process list
	ft_lstadd_back(&data->plist, ft_lstnew(p_data));
}

static void	execute_branch(t_branch_node *branch, t_ctx *ctx)
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

static void	ft_close_fds(t_list *plist)
{
	int		iter;
	t_list	*tmp;

	iter = ft_lstsize(plist);
	tmp = plist;
	while (iter--)
	{
		if (((t_proc *)tmp->content)->fd_io[0] != 0)
			close(((t_proc *)tmp->content)->fd_io[0]);
		if (((t_proc *)tmp->content)->fd_io[1] != 1)
			close(((t_proc *)tmp->content)->fd_io[1]);
		tmp = tmp->next;
	}
}
