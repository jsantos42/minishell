#include "../headers/command_utils.h"

int	is_exit_command(char *input)
{
	if (!ft_strncmp(input, "exit", 5))
	{
		printf("%s\n", input);
		return (1);
	}
	return (0);
}

int	is_a_valid_command(char *cmd, t_data *data)
{
	DIR	*directory;
	int	iter;

	iter = -1;
	while (data->paths[++iter] != NULL)
	{
		directory = opendir(data->paths[iter]);
		if (!directory)
			terminate_program(OPENING_DIR, data);
		if (is_in_dir(cmd, data->paths[iter], directory))
			return (1);
	}
	return (0);
}


void	execute_command(t_data *data)
{
	(void)data;
//	execve();

}


int	is_in_dir(char *input, char *path, DIR *directory)
{
	int	ret;

	struct dirent *dir_struct;

	dir_struct = NULL;
	dir_struct = readdir(directory);
	while (dir_struct)
	{
		if (ft_strncmp(input, dir_struct->d_name, ft_strlen(input) + 1) == 0)
		{
			ret = 1;
			printf("The absolute path of the command is %s/%s\n", path, input);
			break;
		}
		dir_struct = readdir(directory);
	}
	if (dir_struct == NULL)
	{
		ret = 0;
		if (errno == EBADF || errno == EFAULT || errno == EIO)
			handle_error(READING_DIR);
	}
	if (closedir(directory) != 0)
		handle_error(CLOSING_DIR);
	return (ret);
}
