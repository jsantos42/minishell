#include "../headers/quote_char.h"

bool	is_quote_char(char chr)
{
	return (chr == '\'' || chr == '\"');
}

/*
**	This makes sure nothing between quotes gets interpreted as a command.
**	1) It starts by defining which type of quote it's using.
**	2) Creates a new_input string, which will be a copy of input without the
**	pair of quotes it's handling.
**	3) Parses through the input string and copies it to new_input, except for
**	the quote_type char (unless it's escaped). Continues to do so until it finds
**	a closing quote.
**	4) If it found a closing quote, saves the new position (that will be passed
**	to scanner->cursor) and copies the rest of the input string to new_input,
**	NULL-terminating it and returning it.
**	NOTE: when saving the new quote_pos, it uses k (instead of i) because
**	it needs to subtract 2 quote chars from the index count. Plus, it needs to
**	subtract 1 because the iteration on the previous while goes one extra loop.
*/

///this should interpret $!! subject: " inhibit all interpretation of a sequence of characters except for $
char	*handle_quote_char(char *input, int *quote_pos)
{
	char	quote_type;
	char	*new_input;
	int 	quotes_found;
	int		i;
	int		k;
	int		original_quote_pos;

	original_quote_pos = *quote_pos;
	quote_type = *(input + *quote_pos);
	new_input = malloc(ft_strlen(input) + 1 - PAIR_OF_QUOTES);
	if (!new_input)
		terminate_program(MALLOC);
	quotes_found = 0;
	i = 0;
	k = 0;
	while (input[i] != '\0' && quotes_found < 2)
	{
		if (!(input[i] == quote_type
		&& (i == 0 || input[i - 1] != '\\')))
			new_input[k++] = input[i];
		else
			(quotes_found)++;
		i++;
	}
	if (quotes_found < 2)
	{
		free(new_input);
		terminate_program(UNCLOSED_QUOTES);
	}
	*quote_pos += k - 1;
	while (input[i] != '\0')
		new_input[k++] = input[i++];
	new_input[k] = '\0';
	free(input);
	if (quote_type == '\"')
		new_input = look_for_expansions(new_input, original_quote_pos);
	return (new_input);
}


char	*look_for_expansions(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (is_dollar_sign(str[i]) && !is_escaped(str, i))
			str = handle_dollar_sign(str, i);
		else if (is_dollar_sign(str[i]) && is_escaped(str, i))
			str = remove_escape_char(str, --i);
		i++;
	}
	return (str);
}

#define ESCAPECHAR 1

char	*remove_escape_char(char *str, int esc_pos)
{
	char	*new_input;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(str) - ESCAPECHAR;
	new_input = malloc(size + 1);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (i == esc_pos)
			j++;
		new_input[j++] = str[i++];
	}
	new_input[j] = '\0';
	return (new_input);
}

