/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:01:22 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/15 19:59:08 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static char *ft_calloc(int size)
{
	char	*ret;
	int		pos;

	pos = 0;
	ret = malloc(size * sizeof(char));
	if (!ret)
		return (NULL);
	while (pos < size)
	{
		ret[pos] = '\0';
		pos++;
	}
	return (ret);
}

static char	*ft_strjoin(char *s1, char *buf)
{
	int		s1pos;
	int		bufpos;
	int		pos;
	char	*ret;

	pos = 0;
	bufpos = 0;
	s1pos = 0;
	while (buf[bufpos] != '\n' && buf[bufpos])
		bufpos++;
	while (s1[s1pos])
		s1pos++;
	ret = ft_calloc(((bufpos + s1pos + 2)) * sizeof(char));
	if(!ret)
		return (NULL);
	while (pos < bufpos + s1pos + 1)
	{
		if (pos < s1pos)
			ret[pos] = s1[pos];
		else
			ret[pos] = buf[pos - s1pos];
		pos++;
	}
	return (ret);
}

static int	ft_verifyline(char	*str)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '\n')
			return (0);
		pos++;
	}
	return (1);
}

static void ft_movebuf(char *buf)
{
	int	len;
	int	nlpos;
	int	pos;

	len = 0;
	nlpos = 0;
	pos = 0;
	while (buf[len])
		len++;
	while (buf[nlpos] && buf[nlpos] != '\n')
		nlpos++;
	while (nlpos == len && buf[pos])
	{
		buf[pos] = '\0';
		pos++;
	}
	pos = 0;
	while (buf[pos + nlpos + 1])
	{
		buf[pos] = buf[pos + nlpos + 1];
		pos++;
	}
	buf[pos] = '\0';
}

char	*get_next_line(int fd)
{
	static char buffer[1024][BUFFER_SIZE];
	char		*ret;
	int			readvalue;

	readvalue = -1;
	if (fd < 0 || fd > 1024)
		return (NULL);
	if (!buffer[fd] || buffer[fd][0] == '\0')
		readvalue = read(fd, buffer[fd], BUFFER_SIZE);
	if (readvalue == 0)
		return (NULL);
	ret = ft_strjoin("", buffer[fd]);
	if(!ret)
		return (NULL);
	while (readvalue != 0 && ft_verifyline(buffer[fd]) != 0)
	{
		readvalue = read(fd, buffer[fd], BUFFER_SIZE);
		if (readvalue == 0)
		{
			free(ret);
			return (NULL);
		}
		ret = ft_strjoin(ret, buffer[fd]);
		if (!ret)
			return (NULL);
	}
	ft_movebuf(buffer[fd]);
	return (ret);
}
