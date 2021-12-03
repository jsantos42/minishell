#include "../headers/builtins.h"

void	builtin_echo(char **args, int *ctx)
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
}

// static char *ft_get_prev_dir(char *path);

void	builtin_cd(char **args)
{
	char	*cur_dir;
	char	*old_pwd;
	char	*path;

	cur_dir = get_env_var("PWD");

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
	}
	else
		printf("Error changing directory\n");
}

// static char *ft_get_prev_dir(char *path)
// {
// 	int		len;
// 	char	*prev_dir;

// 	len = ft_strlen(path);
// 	while(path[len] != '/')
// 		len--;
// 	prev_dir = ft_substr(path, 0, len);
// 	return (prev_dir);
// }

void	builtin_exit(void)
{
	write_history(".history");
	exit(EXIT_SUCCESS);
}
