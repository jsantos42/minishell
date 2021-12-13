#include "../../headers/executor/heredoc.h"

int	run_heredoc(t_leaf_node *node)
{
	size_t	size;
	char	*heredoc_input;
	int		heredoc_fd;

	node->heredoc_file = ft_strnjoin(4, "tmp/", ".", node->args[0], ".heredoc");
	heredoc_fd = open(node->heredoc_file, O_CREAT | O_APPEND | O_RDWR, 0644);
	size = ft_strlen(node->delimiter);
	heredoc_input = readline("heredoc > ");
	while (heredoc_input && ft_strncmp(heredoc_input, node->delimiter, size + NULLTERM))
	{
		write(heredoc_fd, heredoc_input, ft_strlen(heredoc_input));
		write(heredoc_fd, "\n", 1);
		add_history(heredoc_input);
		free(heredoc_input);
		heredoc_input = readline("heredoc > ");
	}
	close(heredoc_fd);
	return (open(node->heredoc_file, O_RDONLY, 0644));
}
