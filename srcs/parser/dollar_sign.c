/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:38:56 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:39:01 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser/dollar_sign.h"

bool	is_dollar_sign(char chr)
{
	return (chr == '$');
}

/*
**	Finds the name of the variable, calculates it length, and calls
**	replace_input in order to replace the previous input with one that has this
**	variable expanded. Returns the number of added chars.
*/

int	handle_dollar_sign(t_data *data, int *dollar_pos)
{
	t_dollar	d;
	char		*new_input;
	bool		expand_status;

	if (data->escaped)
		return (escape(data, dollar_pos));
	d.name_len = get_var_length(data->input + *dollar_pos + DOLLAR_SIGN);
	d.name = ft_substr(data->input, *dollar_pos + DOLLAR_SIGN, d.name_len);
	if (ft_strncmp(d.name, "?", 2) == 0)
	{
		expand_status = true;
		d.expanded = ft_itoa(data->status);
	}
	else
	{
		expand_status = false;
		d.expanded = getenv(d.name);
	}
	if (!d.expanded)
		d.expanded = ft_strdup("");
	d.expanded_len = ft_strlen(d.expanded);
	new_input = replace_input(data->input, &d, *dollar_pos);
	free(d.name);
	*dollar_pos += d.expanded_len;
	if (expand_status)
		free(d.expanded);
	free(data->input);
	data->input = new_input;
	return (d.expanded_len - d.name_len - DOLLAR_SIGN);
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
		&& !is_quote_char(var[i]) && !is_dollar_sign(var[i])
		&& !is_escape_char(var[i]))
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
		terminate_program("", MALLOC);
	i = 0;
	j = 0;
	while (original[i] != '\0' && i != dollar_pos)
		new[j++] = original[i++];
	i += d->name_len + DOLLAR_SIGN;
	k = 0;
	while (d->expanded[k] != '\0')
		new[j++] = d->expanded[k++];
	while (original[i] != '\0')
		new[j++] = original[i++];
	new[j] = '\0';
	return (new);
}
