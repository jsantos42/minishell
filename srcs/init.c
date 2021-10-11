#include "../headers/init.h"

void	init_data(t_data *data, int argc, char **argv)
{
	char	*env_paths;

	if (argc > 1)
		exit (0);
	(void)argv;
	data->paths = NULL;
	data->input = NULL;
	data->cmd = NULL;
	data->exit_cmd = false;
	env_paths = getenv("PATH");
	if (!env_paths)
		terminate_program(ENV_VAR, data);
	data->paths = ft_split(env_paths, ':', &data->nb_paths);
	if (!data->paths)
		terminate_program(MALLOC, data);
}

void	init_cmd(t_data *data)
{
	data->cmd = NULL;
	if (!ft_other_malloc((void**)&(data->cmd)))
		terminate_program(MALLOC, data);
	data->cmd->command = NULL;
	data->cmd->redir_input = NULL;
	data->cmd->redir_output = NULL;
	data->cmd->arguments = NULL;
	data->cmd->nb_arguments = 0;
	data->cmd->next = NULL;
}
