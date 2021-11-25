#include "../headers/execute_input.h"

#define READ_END 0
#define WRITE_END 1

static void	execute_node(t_tree *node, int *ctx);
static void	execute_leaf(t_leaf_node *leaf, int *ctx);
static void	execute_branch(t_branch_node *branch, int *ctx);
static char	*get_cmd_path(char *cmd, char **paths);
static void	ft_close_fds(t_list *plist);

/*
*	1) Starts by creating a base context to be shared by processes.
*		𝘚𝘛𝘋𝘐𝘕 --𝘙𝘌𝘈𝘋-->[PROCESS]--𝘞𝘙𝘐𝘛𝘌-->𝘚𝘛𝘋𝘖𝘜𝘛
*	2) Evoke the recursion core to traverse through the tree leafs and branches.
*	3) Wait for all the launched processes to finish before returning control.
*/
void	execute_input(t_data *data)
{
	int		ctx[2] = {0, 1};
	int		status;
	size_t	iter;

	// The Recursion Summoner
	execute_node(data->tree, ctx);
	
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

static void	execute_node(t_tree *node, int *ctx)
{
	if (node->type == LEAF_NODE)
		execute_leaf(&node->leaf, ctx);
	else if (node->type == BRANCH_NODE)
		execute_branch(&node->branch, ctx);
}

/*
*	1) Get the command path for the executable file
*	2) Create the child proccess by fork and allocate program data to be pushed
*	to the active processes list.
*	3) !CHILD PROCCESS!
*		1. Copy the ctx FIFO to the proccess STDIO
		2. Close all the oppened file descriptors, to make sure that no
		loose end of the pipes will be left open
		3. Execute the binary.
*	4) Push the recent opened procces infos to the active proccess list.
*/
static void	execute_leaf(t_leaf_node *leaf, int *ctx)
{
	char	*cmd_path;
	t_proc	*p_data;
	t_data	*data;

	data = get_data(NULL);

	cmd_path = get_cmd_path(leaf->args[0], data->paths);

	if (is_builtin(leaf->args[0]))
		exec_builtin(leaf, ctx);
	else
	{
		p_data = malloc(sizeof(t_proc));
		if (!p_data)
			terminate_program(MALLOC);
		p_data->fd_io[0] = ctx[0];
		p_data->fd_io[1] = ctx[1];
		p_data->id = fork();

		if (p_data->id == 0)
		{
			if (dup2(ctx[0], 0) == -1 || dup2(ctx[1], 1) == -1)
				terminate_program(DUP2);
			ft_close_fds(data->plist);
			execve(cmd_path, leaf->args, data->envp);
			perror("No such a file or directory");
		}
		ft_lstadd_back(&data->plist, ft_lstnew(p_data));
	}
}

static void	execute_branch(t_branch_node *branch, int *ctx)
{
	int	p[2];
	int	left_ctx[2];
	int	right_ctx[2];

	pipe(p);

	left_ctx[0] = ctx[0];
	left_ctx[1] = p[WRITE_END];
	execute_node(branch->left, left_ctx);

	right_ctx[1] = ctx[1];
	right_ctx[0] = p[READ_END];
	execute_node(branch->right, right_ctx);
}

static char	*get_cmd_path(char *cmd, char **paths)
{
	char	*part_path;
	char	*path;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
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
