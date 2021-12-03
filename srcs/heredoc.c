#include "../headers/heredoc.h"

void	run_heredoc(t_leaf_node *current_node)
{
	size_t	size;
	char	*heredoc_input;

	size = ft_strlen(current_node->delimiter);
	heredoc_input = readline("heredoc > ");
	while (ft_strncmp(heredoc_input, current_node->delimiter, size + NULLTERM))
	{
		add_history(heredoc_input);
		free(heredoc_input);
		heredoc_input = readline("heredoc > ");
	}
}
