#ifndef LIBFT_EXTRA_H
# define LIBFT_EXTRA_H

char	*ft_strnjoin(int count,...);
void	*xmalloc(size_t size, char *file, int line);
char	**ft_push_to_matrix(char **array, char *str);
void	ft_matrix_del_one(char **array, int	index);

#endif
