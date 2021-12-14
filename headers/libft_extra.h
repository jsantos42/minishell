/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:45:36 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 20:23:39 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_EXTRA_H
# define LIBFT_EXTRA_H

char	*ft_strnjoin(int count, ...);
char	**ft_push_to_matrix(char **array, char *str);
void	ft_matrix_del_one(char **array, int index);
char	**ft_matrix_dup(char **matrix, int items);
void	*xmalloc(size_t size, char *file, int line);

#endif
