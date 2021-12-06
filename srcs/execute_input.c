#include "../headers/execute_input.h"

#define READ_END 0
#define INPUT 0
#define WRITE_END 1
#define OUTPUT 1
#define PIPELINE 2
#define TRUE 1
#define FALSE 0

static void	execute_pipeline(t_tree *node, int *ctx);
static void	execute_leaf(t_tree *node, int *ctx);
static void	execute_branch(t_tree *node, int *ctx);
static char	*get_cmd_path(char *cmd);
static void	ft_close_fds(t_list *plist);
static void	open_files(t_leaf_node *leaf, int *ctx);

/*
*	1) Starts by creating a base context to be shared by processes.
*		𝘚𝘛𝘋𝘐𝘕 --𝘙𝘌𝘈𝘋-->[PROCESS]--𝘞𝘙𝘐𝘛𝘌-->𝘚𝘛𝘋𝘖𝘜𝘛
*	2) Evoke the recursion core to traverse through the tree leafs and branches.
*	3) Wait for all the launched processes to finish before returning control.
*/
void	execute_input(t_data *data)
{
	int		ctx[3] = {0, 1, FALSE};
	int		status;
	size_t	iter;

	if (data->tree->type == LEAF_NODE)
		execute_leaf(data->tree, ctx);
	else
		execute_pipeline(data->tree, ctx);

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

static void	execute_pipeline(t_tree *node, int *ctx)
{
	if (node->type == LEAF_NODE)
		execute_leaf(node, ctx);
	else if (node->type == BRANCH_NODE)
		execute_branch(node, ctx);
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
static void	execute_leaf(t_tree *node, int *ctx)
{
	char	*cmd_path;
	t_proc	*p_data;
	t_data	*data;

	data = get_data(NULL);
	cmd_path = get_cmd_path(node->leaf.args[0]);

	open_files(&node->leaf, ctx);

	if (!ctx[PIPELINE] && is_builtin(node->leaf.args[0]))
		data->status = exec_builtin(&node->leaf, ctx);
	else
	{
		p_data = xmalloc(sizeof(t_proc), __FILE__, __LINE__);
		p_data->fd_io[INPUT] = ctx[INPUT];
		p_data->fd_io[OUTPUT] = ctx[OUTPUT];
		p_data->id = fork();

		if (p_data->id == 0)
		{
			if (dup2(ctx[INPUT], 0) == -1 || dup2(ctx[OUTPUT], 1) == -1)
				terminate_program(DUP2);
			ft_close_fds(data->plist);
			if (is_builtin(node->leaf.args[0]))
				exec_builtin(&node->leaf, ctx);
			execve(cmd_path, node->leaf.args, data->env.array);
			perror("No such a file or directory");
		}
		ft_lstadd_back(&data->plist, ft_lstnew(p_data));
	}
}

static void	execute_branch(t_tree *node, int *ctx)
{
	int	p[2];
	int	left_ctx[3];
	int	right_ctx[3];

	pipe(p);

	left_ctx[INPUT] = ctx[INPUT];
	left_ctx[OUTPUT] = p[WRITE_END];
	left_ctx[PIPELINE] = TRUE;
	execute_pipeline(node->branch.left, left_ctx);

	right_ctx[OUTPUT] = ctx[OUTPUT];
	right_ctx[INPUT] = p[READ_END];
	right_ctx[PIPELINE] = TRUE;
	execute_pipeline(node->branch.right, right_ctx);
}

static char	*get_cmd_path(char *cmd)
{
	char	**paths;
	char	*path;
	t_data	*data;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	
	data = get_data(NULL);
	paths = ft_split(get_env_var("PATH"), ':', NULL);

	i = 0;
	while (paths[i])
	{
		path = ft_strnjoin(3, paths[i], "/", cmd);
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

static void	open_files(t_leaf_node *leaf, int *ctx)
{
	if (leaf->redir_input)
		ctx[INPUT] = open(leaf->redir_input, O_RDONLY, 0);

	if (leaf->redir_output && leaf->append_mode)
		ctx[OUTPUT] = open(leaf->redir_output, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (leaf->redir_output)
		ctx[OUTPUT] = open(leaf->redir_output, O_CREAT | O_TRUNC | O_WRONLY, 0644);
}