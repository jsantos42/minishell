#include "../headers/redirect_input.h"

/* Change this function, because:
 * According to the maintainers of bash:
 * The here document delimiter does not undergo any expansions except quote
//removal, so the delimiter is the literal string `$PATH'.
The here document delimiter does not undergo any expansions except quote
		removal, so the delimiter is the literal string `$PATH'. The lines of the
here-document undergo a different set of expansions, which happen after the
check for the delimiter is performed, which means that you need to have a
		line that consists solely of `$PATH' to terminate the here-document (as you
discovered). I cannot see how you're going to be able to do anything useful
with this construct; it just seems too clever by (more than) half.
The delimiter is not what you think it is. The delimiter for a here-
document is a shell word (which can include quoted substrings), and after
it undergoes the appropriate quote removal, your delimiter is
"ola\nI,\nola\nola" (using C string notation).

Now, you're never going to be able to match this; it contains a newline.
When the shell constructs the here-document body, it reads individual lines
		from the input source and, after removing the trailing newline, tries to
		match them against the delimiter (and backslash doesn't work to quote the
newline). This will obviously never match a delimiter containing a newline.
Some shells (e.g., yash) choose to make this a syntax error. Bash does not.
*/

/*
**	Note: on heredoc, bash does not interpret the '$' as a variable expansion,
**	that's why this function only calls handle_dollar_sign when it's not on
**	here_doc mode.
*/

void	handle_input_redirection(t_tree **current_node, t_data *data, int *i)
{
	char	*redir;
	bool	interpret_dollar;

	(*i)++;
	if (data->input[*i] == '<')
	{
		(*current_node)->leaf.here_doc = true;
		(*i)++;
	}
	skip_white_space(data->input, i);
	interpret_dollar = !(*current_node)->leaf.here_doc;
	redir = parser_core(data, i, interpret_dollar);
	if ((*current_node)->leaf.here_doc)
		(*current_node)->leaf.delimiter = redir;
	else
		(*current_node)->leaf.redir_input = redir;
}
