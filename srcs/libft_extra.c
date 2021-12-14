/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:11:57 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/14 14:12:00 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

char	*ft_strnjoin(int count, ...)
{
	char	*new;
	char	*tmp;
	va_list	args;
	int		size;
	int		i;

	size = 0;
	i = -1;
	va_start(args, count);
	while (++i < count)
		size += ft_strlen(va_arg(args, char *));
	va_end(args);
	new = calloc(size + 1, sizeof(char));
	if (!new)
		return (NULL);
	va_start(args, count);
	i = -1;
	while (++i < count)
	{
		tmp = va_arg(args, char *);
		ft_strlcat(new, tmp, size + 1);
	}
	va_end(args);
	return (new);
}

char	**ft_push_to_matrix(char **array, char *str)
{
	char	**new;
	int		iter;

	iter = -1;
	while (array[++iter])
		;
	new = xmalloc(sizeof(char *) * (iter + 2), __FILE__, __LINE__);
	iter = -1;
	while (array[++iter])
		new[iter] = array[iter];
	new[iter] = str;
	new[++iter] = NULL;
	free(array);
	return (new);
}

void	ft_matrix_del_one(char **array, int index)
{
	while (array[index])
	{
		array[index] = array[index + 1];
		index++;
	}
}

char	**ft_matrix_dup(char **matrix, int items)
{
	char	**new;
	int		iter;

	new = xmalloc(sizeof(char *) * (items + 1), __FILE__, __LINE__);
	iter = -1;
	while (matrix[++iter])
		new[iter] = matrix[iter];
	new[iter] = NULL;
	return (new);
}

char	*ft_strstr(const char *str1, const char *str2)
{
	size_t	n;

	n = ft_strlen(str2);
	if (*str2 == '\0')
		return ((char *)str1);
	if (n == 0)
		return (NULL);
	while (*str1)
	{
		if (!ft_memcmp(str1, str2, n))
			return ((char *)str1);
		str1++;
	}
	return (NULL);
}
