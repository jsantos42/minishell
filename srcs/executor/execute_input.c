/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:26:49 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/14 14:06:54 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executor/execute_input.h"

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

/*
*	1) Starts by creating a base context to be shared by processes.
*		ctx[0] = INPUT | ctx[1] = OUTPUT | ctx[3] = PIPELINE_FLAG
*			𝘚𝘛𝘋𝘐𝘕 --𝘙𝘌𝘈𝘋-->[PROCESS]--𝘞𝘙𝘐𝘛𝘌-->𝘚𝘛𝘋𝘖𝘜𝘛
*	2) If the tree is a single cmd, execute the leaf. Otherwise, evoke the
*	recursion core to traverse through the tree leafs and branches.
*	3) Block execution and wait for all the launched processes to finish
*	before returning control. Clear the proccess list at the end.
*	4) Update the status with the  exit code of the last process.
*/
void	execute_input(t_data *data)
{
	int			*ctx;
	t_list		*active_proc;		

	ctx = (int [3]){0, 1, FALSE};
	if (data->tree->type == LEAF_NODE)
		execute_leaf(data, &data->tree->leaf, ctx);
	else
		execute_pipeline(data->tree, ctx);
	active_proc = data->plist;
	while (active_proc)
	{
		waitpid(*((pid_t *)active_proc->content), &data->status, 0);
		active_proc = active_proc->next;
	}
	ft_lstclear(&data->plist, free);
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
	if (!ctx[PIPELINE] && leaf->args && ctx[INPUT] != -1
		&& is_builtin(leaf->args[0]))
		data->status = exec_builtin(leaf, ctx);
	else if (leaf->args && ctx[INPUT] != -1)
	{
		child = xmalloc(sizeof(pid_t), __FILE__, __LINE__);
		*child = fork();
		if (*child == 0)
		{
			if (dup2(ctx[INPUT], 0) == -1 || dup2(ctx[OUTPUT], 1) == -1)
				terminate_program(leaf->args[0], DUP2);
			if (is_builtin(leaf->args[0]))
				exec_builtin(leaf, ctx);
			ft_close_fds(leaf, ctx);
			cmd_path = get_cmd_path(leaf->args[0]);
			execve(cmd_path, leaf->args, data->env.array);
			terminate_program(leaf->args[0], CMD_NOT_FOUND);
		}
		ft_lstadd_back(&data->plist, ft_lstnew(child));
	}
	ft_close_fds(leaf, ctx);
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
