/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:56:21 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/15 17:58:32 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/*static void	ft_putstr(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		write(1, &str[pos], 1);
		pos++;
	}
}*/

static int	ft_checkendline(char *str)
{
	int pos;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '\n')
			return (1);
		pos++;
	}
	return (0);
}

static char *ft_strjoin(char *s1, char *s2)
{
	int		s1pos;
	int		s2pos;
	char	*tmp;

	s1pos = 0;
	s2pos = 0;
	while (s1[s1pos])
		s1pos++;
	while (s2[s2pos])
		s2pos++;
	tmp = malloc((s1pos + s2pos + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	s1pos = 0;
	s2pos = 0;
	while (s1[s1pos])
	{
		tmp[s1pos] = s1[s1pos];
		s1pos++;
	}
	while (s2[s2pos])
	{
		tmp[s1pos + s2pos] = s2[s2pos];
		s2pos++;
	}
	tmp[s1pos + s2pos] = '\0';
	return (tmp);
}
static char	*ft_copy(char *src)
{
	char	*dst;
	int		pos;
	int		srcpos;
	int		size;
	
	size = 0;
	while (src[size] != '\n' && src[size] != '\0')
		size++;
	if (size == 0 && src[0] == '\0')
	{
		dst = malloc(1);
		return (dst);
	}
	size += 2;
	dst = malloc((size) * sizeof(char));
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
	char		*tmp;
	int			readvalue;

	readvalue = -1;
	while (ft_checkendline(buffer[fd]) != 1 && readvalue != 0)
	{	
		if (readvalue == -1)
			tmp = ft_copy(buffer[fd]);
		else
			tmp = ft_strjoin(tmp, buffer[fd]);
		if (!tmp)
			return (NULL);
		readvalue = read(fd, buffer[fd], BUFFER_SIZE);
	}
	if (readvalue == 0 || ft_checkendline(buffer[fd]) == 0)
	{
		free(tmp);
		return (NULL);
	}
	if (readvalue != -1)
	{
		printed = ft_copy(tmp);
		tmp = ft_copy(buffer[fd]);
		printed = ft_strjoin(printed, tmp);
		free(tmp);
	}
	else
		return (NULL);
	return (printed);
}

/*int	main(void)
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
	close(fd);
	close(fd1);
	return (0);
}*/
