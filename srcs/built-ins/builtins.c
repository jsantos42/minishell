#include "../../headers/built-ins/builtins.h"

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

static char	*get_dir_path(char *arg);

int	__cd(char **args, int *ctx)
{
	char	*old_pwd;
	char	*path;

	(void)ctx;
	path = get_dir_path(args[1]);
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != -1)
	{
		update_env_var("OLDPWD", old_pwd);
		update_env_var("PWD", getcwd(NULL, 0));
		free(path);
		return (0);
	}
	if (errno == ENOTDIR)
		printf("Minishell: cd: %s: Not a directory\n", path);
	else if (errno == ENOENT)
		printf("Minishell: cd: %s: No such file or directory\n", path);
	else if (errno == EACCES)
		printf("Minishell: cd: %s: Permission denied\n", path);
	free(path);
	return (1);
}

static char	*get_dir_path(char *path)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (!path || !ft_strncmp(path, "~", 2))
		return (ft_strdup(get_env_var("HOME")));
	else if (!ft_strncmp(path, "-", 2))
		return (ft_strdup(get_env_var("OLDPWD")));
	else if (!ft_strncmp(path, "~/", 2))
		return (ft_strnjoin(3, get_env_var("HOME"), "/", path));
	else if (!ft_strncmp(path, "./", 2) || !ft_strncmp(path, "../", 3))
		return (ft_strnjoin(3, cur_dir, "/", path));
	else
		return (ft_strdup(path));
}

int	__exit(char **args, int *ctx)
{
	(void)args;
	(void)ctx;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
	return (0);
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
