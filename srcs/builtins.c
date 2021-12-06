#include "../headers/builtins.h"

int	__echo(char **args, int *ctx)
{
	int		iter;
	bool	new_line;
	bool	print_space;
	
	iter = 1;
	if (args[iter] && !ft_strncmp(args[iter], "-n", 3))
	{
		new_line = false;
		iter = 2;
	}
	else
		new_line = true;
	print_space = false;
	while (args[iter])
	{
		if (print_space)
			write(ctx[1], " ", 1);
		else
			print_space = true;
		write(ctx[1], args[iter], ft_strlen(args[iter]));
		iter++;
	}
	if (new_line)
		write(ctx[1], "\n", 1);
	return (0);
}

// static char *ft_get_prev_dir(char *path);

int	__cd(char **args, int *ctx)
{
	char	*cur_dir;
	char	*old_pwd;
	char	*path;

	cur_dir = get_env_var("PWD");
	(void)ctx;
	if (!args[1] || !ft_strncmp(args[1], "~", 2))
		path = get_env_var("HOME");
	else if (!ft_strncmp(args[1], "-", 2))
		path = get_env_var("OLDPWD");
	else if (!ft_strncmp(args[1], "~/", 2))
		path = ft_strnjoin(3, get_env_var("HOME"), "/", &args[1][2]);
	else if (!ft_strncmp(args[1], "./", 2) || !ft_strncmp(args[1], "../", 3))
		path = ft_strnjoin(3, cur_dir, "/", args[1]);
	else
		path = args[1];
	old_pwd = getcwd(NULL, 0);
	if(chdir(path) != -1)
	{
		update_env_var("OLDPWD", old_pwd);
		update_env_var("PWD", getcwd(NULL, 0));
		return (0);
	}
	printf("Error changing directory\n");
	return (1);
}

int	__exit(char **args, int *ctx)
{
	(void)args;
	(void)ctx;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
	return(0);
}

int	__pwd(char **args, int *ctx)
{
	char	*cwd;
	
	(void)args;
	(void)ctx;
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
