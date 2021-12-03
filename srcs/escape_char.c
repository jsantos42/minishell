#include "../headers/escape_char.h"

/*
**	Receives the str from which to remove the escape char, and the index of the
**	escaped character (NOT the '\\' itself, the next one).
**
**	NOTE: the first condition is needed for those cases with multiple contiguous
**	escape chars (ex: escaping an escape char "\\", escaping an escape char
**	followed by escaping any other char "\\\a", etc.).
*/

char	*remove_escape_char(char *str, int *escaped_char)
{
	char	*new_input;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(str);
	if (str[*escaped_char] == '\\' && str[*escaped_char - 2] != '\\')
		return (str);
	new_input = malloc(size - ESCAPECHAR + 1);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (i == *escaped_char - 1 || (i == 0 && *escaped_char == 0))
			i++;
		new_input[j++] = str[i++];
	}
	new_input[j] = '\0';
	(*escaped_char)--;
	return (new_input);
}
