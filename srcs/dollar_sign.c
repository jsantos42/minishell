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

void	handle_dollar_sign(t_data *data, int dollar_pos)
{
	t_dollar	dollar;
	char	*new_input;

//	this protection against escape should make the special char part of the argument
//	if (dollar_pos != 0 && --dollar_pos == '\\')
//		return ;
	dollar.name_len = DOLLAR_SIGN + get_var_length(data->input + dollar_pos);
	dollar.name = ft_substr(data->input, dollar_pos + 1, dollar.name_len);
	dollar.expanded = getenv(dollar.name);
	dollar.expanded_len = ft_strlen(dollar.expanded);
	new_input = replace_input(data->input, &dollar, dollar_pos);
	free(dollar.name);
	free(dollar.expanded);
	free(data->input);
	data->input = new_input;
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

char	*replace_input(char *original, t_dollar *dollar, int dollar_pos)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	new = malloc(ft_strlen(original) - dollar->name_len + dollar->expanded_len + 1);
	if (!new)
		terminate_program(MALLOC);
	i = 0;
	j = 0;
	while (original[i] != '\0' && i != dollar_pos)
		new[j++] = original[i++];
	while (dollar->name_len--)
		i++;
	k = 0;
	while (dollar->expanded[k] != '\0')
		new[j++] = dollar->expanded[k++];
	while (original[i] != '\0')
		new[j++] = original[i++];
	new[j] = '\0';
	return (new);
}
