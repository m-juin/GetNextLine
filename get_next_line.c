/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:56:21 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/14 13:34:08 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void	ft_putstr(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		write(1, &str[pos], 1);
		pos++;
	}
}

static char	*ft_copy(char *src, int size)
{
	char	*dst;
	int		pos;
	int		srcpos;

	dst = malloc((size + 1) * sizeof(char));
	pos = 0;
	if (!dst)
		return (NULL);
	while (pos < size)
	{
		srcpos = 0;
		dst[pos] = src[srcpos];
		while (src[srcpos])
		{
			src[srcpos] = src[srcpos + 1];
			srcpos++;
		}
		pos++;
	}
	dst[pos] = '\0';
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE];
	char		*printed;
	int			pos;
	int			readvalue;

	pos = 0;
	while (buffer[fd][pos] != '\n' && buffer[fd][pos] != '\0')
		pos++;
	if (pos > 0 && buffer[fd][pos] == '\n')
	{
		printed = ft_copy(buffer[fd], pos + 1);
		if (!printed)
			return (NULL);
	}
	else
	{
		if (pos != 0 && buffer[fd][pos] == '\0')
			ft_putstr(buffer[fd]);
		pos = 0;
		readvalue = read(fd, buffer[fd], BUFFER_SIZE);
		if (readvalue == 0)
			return (NULL);
		while (buffer[fd][pos] != '\n' && buffer[fd][pos] != '\0')
			pos++;
		if (pos > 0 && buffer[fd][pos] == '\n')
		{
			printed = ft_copy(buffer[fd], pos + 1);
			if (!printed)
				return (NULL);
		}
	}
	return (printed);
}

int	main(void)
{
	int	fd;
	int	fd1;

	fd = open("42", O_RDONLY);
	if(fd == -1)
	{
		ft_putstr("open() error");
		return (0);
	}
	fd1 = open("43", O_RDONLY);
	if(fd1 == -1)
	{
		ft_putstr("open() error");
		return (0);
	}
	ft_putstr(get_next_line(fd));
	ft_putstr(get_next_line(fd1));
	ft_putstr(get_next_line(fd));
	close(fd);
	close(fd1);
	return (0);
}
