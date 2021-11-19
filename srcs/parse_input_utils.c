#include "../headers/parse_input_utils.h"

void	skip_white_space(char *input, int *i)
{
	while (input[*i] != '\0' && ft_isspace(input[*i]))
		(*i)++;
}





/*
**	Do edge case for situations when the command is on the same folder (./minishell)
*/

int	is_a_valid_command(t_data *data, char *cmd)
{
	DIR	*directory;
	int	iter;

	iter = -1;
	while (data->paths[++iter] != NULL)
	{
		directory = opendir(data->paths[iter]);
		if (!directory)
			terminate_program(OPENING_DIR);
		if (is_in_dir(cmd, data->paths[iter], directory))
			return (1);
	}
	return (0);
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
			terminate_program(READING_DIR);
	}
	if (closedir(directory) != 0)
		terminate_program(CLOSING_DIR);
	return (ret);
}
