/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:58:17 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/10 19:58:28 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
**	NOTE: when saving the new opening_quote, it uses j (instead of i) because
**	it needs to subtract 2 quote chars from the index count. Plus, it needs to
**	subtract 1 because the iteration on the previous while goes one extra loop.
*/

void	handle_quote_char(t_data *data, int *opening_quote)
{
	int		closing_quote;
	char	*new_input;

	if (data->escaped)
	{
		escape(data, opening_quote);
		return ;
	}
	closing_quote = get_closing_quote(data, *opening_quote);
	if (!closing_quote)
		return ;
	if (data->input[*opening_quote] == '\"')
		look_for_expansions(data, *opening_quote, &closing_quote);
	new_input = remove_quotes(data, opening_quote, closing_quote);
	free(data->input);
	data->input = new_input;
}

/*
**	Gets the position of the closing quote. If it doesn't find a closing quote,
**	sets on the flag forbidden_chars, since the program should not handle
**	unclosed quotes.
*/

int	get_closing_quote(t_data *data, int i)
{
	char	quote_type;

	quote_type = data->input[i];
	while (data->input[++i] != '\0')
	{
		if (data->input[i] == quote_type && !is_escaped(data->input, i))
			return (i);
	}
	data->forbidden_chars = true;
	return (0);
}

/*
**	Looks for variables to expand inside the quoted string. It also updates the
**	closing_quote position (which in this function is named 'end'). Note that
**	this function is called only if the quote_type is '\"'.
*/

void	look_for_expansions(t_data *data, int i, int *end)
{
	while (i < *end)
	{
		if (is_escape_char(data->input[i])
			&& (is_dollar_sign(data->input[i + 1])
				|| data->input[i + 1] == '\"'))
			*end -= remove_escape_char(data, &i);
		else if (is_dollar_sign(data->input[i]))
			*end += handle_dollar_sign(data, &i);
		else
		{
			data->escaped = false;
			i++;
		}
	}
}

char	*remove_quotes(t_data *data, int *opening_quote, int closing_quote)
{
	char	*new_input;
	int		i;
	int		j;

	new_input = malloc(ft_strlen(data->input) - 2 * QUOTE_CHAR + 1);
	if (!new_input)
		terminate_program("", MALLOC);
	i = -1;
	j = -1;
	while (data->input[++i] != '\0')
	{
		if (i == *opening_quote || i == closing_quote)
			continue ;
		new_input[++j] = data->input[i];
		if (i > *opening_quote && i <= closing_quote)
			(*opening_quote)++;
	}
	new_input[++j] = '\0';
	return (new_input);
}
