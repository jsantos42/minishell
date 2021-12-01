#include "../headers/special_chars.h"

bool	is_special_char(char chr)
{
	if (chr == '|' || chr == '&' || chr == '<' || chr == '>'
		|| chr == '\\' || chr == ';')
		return (true);
	else
		return (false);
}

void	handle_pipe(t_tree **current_node, char *str, int *i)
{
	int	operator;

//	this protection against escape should make the special char part of the argument
//	if (*i != 0 && str[*i - 1] == '\\')
//		return ;
	operator = PIPE;
	if (str[++*i] == '|')
	{
		operator = OR;
		(*i)++;
	}
	relink(current_node, operator);
}

void	handle_amper(t_tree **current_node, char *str, int *i)
{
	int	operator;

//	this protection against escape should make the special char part of the argument
//	if (*i != 0 && str[*i - 1] == '\\')
//		return ;
	operator = 0;
	if (str[++*i] == '&')
	{
		operator = AND;
		(*i)++;
	}
	else
		terminate_program(RUN_BG);
	relink(current_node, operator);
}

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

void	handle_input_redirection(t_tree **current_node, char **str, int *i)
{
	int	old_i;

//	this protection against escape should make the special char part of the argument
//	if (*i != 0 && (*str)[*i - 1] == '\\')
//		return ;
	(*i)++;
	if ((*str)[*i] == '<')
	{
		(*current_node)->leaf.here_doc = true;
		(*i)++;
	}
	skip_white_space(*str, i);
	old_i = *i;
	while ((*str)[*i] != '\0'
		   && !is_special_char((*str)[*i])
		   && !ft_isspace((*str)[*i]))
	{
		if (is_quote_char((*str)[*i]))
			*str = handle_quote_char(*str, i);
		else if (is_dollar_sign((*str)[*i]) && !(*current_node)->leaf.here_doc)
			*str = handle_dollar_sign(*str, *i);
	}
	if (*i != old_i && (*current_node)->leaf.here_doc == false)
		(*current_node)->leaf.redir_input = ft_substr(*str, old_i, *i);
	else if (i != 0 && (*current_node)->leaf.here_doc == true)
		(*current_node)->leaf.delimiter = ft_substr(*str, old_i, *i);
}


void	handle_output_redirection(t_tree **current_node, char **str, int *i)
{
	int	old_i;

//	this protection against escape should make the special char part of the argument
//	if (*i != 0 && (*str)[*i - 1] == '\\')
//		return ;
	(*i)++;
	if ((*str)[*i] == '>')
	{
		(*current_node)->leaf.append_mode = true;
		(*i)++;
	}
	skip_white_space(*str, i);
	old_i = *i;
	while ((*str)[*i] != '\0'
		   && !is_special_char((*str)[*i])
		   && !ft_isspace((*str)[*i]))
	{
		if (is_quote_char((*str)[*i]))
			*str = handle_quote_char(*str, i);
		else if (is_dollar_sign((*str)[*i]))
			*str = handle_dollar_sign(*str, *i);
	}
	if (*i != old_i)
		(*current_node)->leaf.redir_output = ft_substr(*str, old_i, *i);
}