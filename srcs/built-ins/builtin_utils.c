#include "../../headers/built-ins/builtins.h"

#define INPUT 0
#define OUTPUT 1
#define PIPELINE 2
#define TRUE 1
#define FALSE 0

bool	is_builtin(char *cmd)
{
	if (strstr("__echo__cd__pwd__export__unset__env__exit__", cmd))
		return (true);
	return (false);
}

int	exec_builtin(t_leaf_node *leaf, int *ctx)
{
	const char *keys[8] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	ft_builtin	builtin[8] = {
		__echo, __cd, __pwd, __export, __unset, __env, __exit, NULL};
	int cmd;
	int	ret;

	cmd = -1;
	while(keys[++cmd])
		if (!ft_strncmp(keys[cmd], leaf->args[0], ft_strlen(keys[cmd]) + 1))
			ret = builtin[cmd](leaf->args, ctx);

	if (ctx[PIPELINE] == TRUE)
		exit(ret);
	
	return (ret);
}