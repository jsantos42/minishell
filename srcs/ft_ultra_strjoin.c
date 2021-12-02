#include <stdarg.h>
#include <string.h>
#include "main.h"

char	*ft_ultra_strjoin(int count,...)
{
	char	*new;
	char	*tmp;
	va_list args;
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
		ft_strlcat(new, tmp, size);
	}
	va_end(args);
	return (new);
}
