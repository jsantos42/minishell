#include "../headers/builtins.h"

bool	is_builtin(char *cmd)
{
	static char *builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int	iter;

	iter = -1;
	while (builtins[++iter])
		if (!ft_strncmp(cmd, builtins[iter], ft_strlen(cmd)))
			return (true);
	return (false);
}

void	exec_builtin(t_leaf_node *leaf, int *ctx)
{
	static char *builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int cmd;

	cmd = -1;
	while(builtins[++cmd])
		if (!ft_strncmp(builtins[cmd], leaf->args[0], ft_strlen(leaf->args[0])))
			break;

	if (cmd == __echo)
		builtin_echo(leaf->args, ctx);
	else if (cmd == __cd)
		builtin_cd(leaf->args);
	// else if (cmd == __pwd)
	// 	builtin_pwd(leaf->args);
	else if (cmd == __export)
		builtin_export(get_data(NULL), leaf->args, ctx);
	// else if (cmd == __unset)
	// 	builtin_unset(leaf->args);
	else if (cmd == __env)
		builtin_env(ctx);
	else if (cmd == __exit)
		builtin_exit();
}