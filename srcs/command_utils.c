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

int	is_a_valid_command(char *input, char **paths)
{
	DIR	*directory;
	int	iter;

	iter = -1;
	while (paths[++iter] != NULL)
	{
		directory = opendir(paths[iter]);
		if (!directory)
			handle_error(OPENING_DIR);
		if (is_in_dir(input, directory))
			return (1);
	}
	return (0);
}

int	is_in_dir(char *input, DIR *directory)
{
	struct dirent *dir_struct;

	while (1)
	{
		dir_struct = readdir(directory);
		if (dir_struct != NULL)
		{
			if (ft_strncmp(input, dir_struct->d_name, ft_strlen(input) + 1) == 0)
				return (1);
		}
		else
		{
			if (errno == EBADF || errno == EFAULT || errno == EIO)
				handle_error(READING_DIR);
			if (closedir(directory) != 0)
				handle_error(CLOSING_DIR);
			return (0);
		}
	}


}
