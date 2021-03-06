/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:11:57 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/14 17:17:35 by pbielik          ###   ########.fr       */
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
	int		iter;

	iter = -1;
	while (array[++iter])
		;
	array = realloc(array, sizeof(char *) * (iter + 2));
	iter = -1;
	while (array[++iter])
		array[iter] = array[iter];
	array[iter] = ft_strdup(str);
	array[++iter] = NULL;
	return (array);
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
		new[iter] = ft_strdup(matrix[iter]);
	new[iter] = NULL;
	return (new);
}

void	*xmalloc(size_t size, char *file, int line)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (ptr == NULL)
	{
		perror(file);
		perror("_");
		perror(ft_itoa(line));
		perror(" : Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
