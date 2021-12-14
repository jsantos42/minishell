/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:50:11 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 20:20:20 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/built-ins/__cd.h"

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
