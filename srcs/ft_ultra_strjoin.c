#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_ultra_strjoin(int count,...)
{
	char	*new;
	va_list args;
	int		size;
	int		i;

	size = 0;
	i = -1;
	va_start(args, count);
	while (++i < count)
		size += strlen(va_arg(args, char *));
	va_end(args);
	va_start(args, count);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
		strcat(new, va_arg(args, char *));
	va_end(args);
	return (new);
}