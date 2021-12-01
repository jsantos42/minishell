#include "../headers/dollar_sign.h"

bool	is_dollar_sign(char chr)
{
	return (chr == '$');
}

/*
**	Finds the name of the variable, calculates it length, and calls
**	replace_input in order to replace the previous input with one that has this
**	variable expanded.
*/

char	*handle_dollar_sign(char *input, int dollar_pos)
{
	t_dollar	d;
	char	*new_input;

//	this protection against escape should make the special char part of the argument
//	if (dollar_pos != 0 && --dollar_pos == '\\')
//		return ;
	d.name_len = get_var_length(input + dollar_pos + DOLLAR_SIGN);
	d.name = ft_substr(input, dollar_pos + DOLLAR_SIGN, d.name_len);
	d.expanded = getenv(d.name);
	if (!d.expanded)
		d.expanded = ft_strdup("");
	d.expanded_len = ft_strlen(d.expanded);
	new_input = replace_input(input, &d, dollar_pos);
	free(d.name);
	free(input);
	return (new_input);
}

/*
**	Finds the length of the unexpanded VAR name and returns it.
*/

int	get_var_length(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0'
	&& !ft_isspace(var[i]) && !is_special_char(var[i])
	&& !is_quote_char(var[i]) && !is_dollar_sign(var[i]))
		i++;
	return (i);
}

/*
**	This replaces the data->input string with a copy that replaces "$VAR" with
**	the corresponding expanded value of VAR in the environment.
*/

char	*replace_input(char *original, t_dollar *d, int dollar_pos)
{
	char	*new;
	int		i;
	int		j;
	int		k;
	int		size;

	size = ft_strlen(original) - DOLLAR_SIGN - d->name_len + d->expanded_len;
	new = malloc(size + 1);
	if (!new)
		terminate_program(MALLOC);
	i = 0;
	j = 0;
	while (original[i] != '\0' && i != dollar_pos)
		new[j++] = original[i++];
	i += DOLLAR_SIGN;
	while (d->name_len--)
		i++;
	k = 0;
	while (d->expanded[k] != '\0')
		new[j++] = d->expanded[k++];
	while (original[i] != '\0')
		new[j++] = original[i++];
	new[j] = '\0';
	return (new);
}
