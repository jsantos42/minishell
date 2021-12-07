#include "../headers/execute_input.h"

#define READ_END 0
#define INPUT 0
#define WRITE_END 1
#define OUTPUT 1
#define PIPELINE 2
#define TRUE 1
#define FALSE 0

static void	execute_pipeline(t_tree *node, int *ctx);
static void	execute_leaf(t_data *data, t_leaf_node *leaf, int *ctx);
static void	execute_branch(t_tree *node, int *ctx);
static char	*get_cmd_path(char *cmd);
static void	ft_close_fds(int *ctx);
static void	open_io_files(t_leaf_node *leaf, int *ctx);

/*
*	1) Starts by creating a base context to be shared by processes.
*			𝘚𝘛𝘋𝘐𝘕 --𝘙𝘌𝘈𝘋-->[PROCESS]--𝘞𝘙𝘐𝘛𝘌-->𝘚𝘛𝘋𝘖𝘜𝘛
*	2) Evoke the recursion core to traverse through the tree leafs and branches.
*	3) Block execution and wait for all the launched processes to finish
*	before returning control.
*/
void	execute_input(t_data *data)
{
	int			*ctx;
	int			status;
	t_list		*active_proc;		

	ctx = (int [3]){0, 1, FALSE};
	if (data->tree->type == LEAF_NODE)
		execute_leaf(data, &data->tree->leaf, ctx);
	else
		execute_pipeline(data->tree, ctx);
	active_proc = data->plist;
	while (active_proc)
	{
		waitpid(*((pid_t *)active_proc->content), &status, 0);
		active_proc = active_proc->next;
	}
	ft_lstclear(&data->plist, free);
	data->status = WEXITSTATUS(status);
}

static void	execute_pipeline(t_tree *node, int *ctx)
{
	if (node->type == LEAF_NODE)
		execute_leaf(get_data(NULL), &node->leaf, ctx);
	else if (node->type == BRANCH_NODE)
		execute_branch(node, ctx);
}

/*
*	1) Open the redicirection files if needed and overwrite the ctx FIFO.
*	2) If the cmd is a builtin and is not inside a pipeline, execute the
*	respective function inside the main process. Saving the result in the
*	data->status. In this cenario, the exec_builtin does not exit!
*	3) If the cmd is not null, create a Child process and push its PID to
*	the active proccess list.
*	4) !CHILD PROCCESS!
*		1. Copy the ctx FIFO to the proccess STDIO.
*		2. Close all the oppened file descriptors, to make sure that no
*		loose ends of the pipes will be left open.
*		3. If the cmd is a builtin, execute it and exit the child.
*		4. Get the path to the binary of the comand by traversing and testing
*		the paths avaible on env.
*		5. Try to execute the given path, if the command exist and execve
*		succeed, the child is exited by execve. Otherwise, the child is
*		terminated with an error message.
*	5) Close the used file descriptor that still open at the main process.
*/
static void	execute_leaf(t_data *data, t_leaf_node *leaf, int *ctx)
{
	char	*cmd_path;
	pid_t	*child;

	open_io_files(leaf, ctx);
	if (!ctx[PIPELINE] && leaf->args && is_builtin(leaf->args[0]))
		data->status = exec_builtin(leaf, ctx);
	else if (leaf->args)
	{
		child = xmalloc(sizeof(pid_t), __FILE__, __LINE__);
		*child = fork();
		if (*child == 0)
		{
			if (dup2(ctx[INPUT], 0) == -1 || dup2(ctx[OUTPUT], 1) == -1)
				terminate_program(leaf->args[0], DUP2);
			ft_close_fds(ctx);
			if (is_builtin(leaf->args[0]))
				exec_builtin(leaf, ctx);
			cmd_path = get_cmd_path(leaf->args[0]);
			execve(cmd_path, leaf->args, data->env.array);
			terminate_program(leaf->args[0], CMD_NOT_FOUND);
		}
		ft_lstadd_back(&data->plist, ft_lstnew(child));
	}
	ft_close_fds(ctx);
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

static void	ft_close_fds(int *ctx)
{
	if (ctx[INPUT] != STDIN_FILENO)
		close(ctx[INPUT]);
	if (ctx[OUTPUT] != STDOUT_FILENO)
		close(ctx[OUTPUT]);
}

static void	open_io_files(t_leaf_node *leaf, int *ctx)
{
	const char	*redir_in = leaf->redir_input;
	const char	*redir_out = leaf->redir_output;
	const bool	append_mode = leaf->append_mode;

	if (redir_in)
		ctx[INPUT] = open(redir_in, O_RDONLY, 0);
	if (redir_out && append_mode)
		ctx[OUTPUT] = open(redir_out, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (redir_out)
		ctx[OUTPUT] = open(redir_out, O_CREAT | O_TRUNC | O_WRONLY, 0644);
}
