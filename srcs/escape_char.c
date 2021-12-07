#include "../headers/escape_char.h"

bool	is_escape_char(char chr)
{
	return (chr == '\\');
}

bool	is_escaped(char *str, int i)
{
	return (i != 0 && str[i - 1] == '\\');
}

/*
**	Receives the str from which to remove the escape char, and the index of the
**	escaped character (NOT the '\\' itself, the next one).
**
**	NOTE: the first condition is needed for those cases with multiple contiguous
**	escape chars (ex: escaping an escape char "\\", escaping an escape char
**	followed by escaping any other char "\\\a", etc.). This same conditions does
**	not interfere with the edge case of "\\" at the end of the input string.
*/

void	remove_escape_char(t_data *data, int *escaped_char)
{
	char	*new_input;
	int		size;
	int		i;
	int		j;

	if (data->escaped)
	{
		data->escaped = false;
		(*escaped_char)++;
		return ;
	}
	size = ft_strlen(data->input);
	new_input = malloc(size - ESCAPECHAR + 1);
	i = 0;
	j = 0;
	while (data->input[i] != '\0')
	{
		if (i == *escaped_char)
			i++;
		else
			new_input[j++] = data->input[i++];
	}
	new_input[j] = '\0';
//	(*escaped_char)--;
	data->escaped = true;
	free(data->input);
	data->input = new_input;
}
