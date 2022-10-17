/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:01:22 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/17 11:34:13 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

static int	ft_getline(char *src)
{
	int	pos;

	pos = 0;
	if (!src)
		return (0);
	while (src[pos])
	{
		if (src[pos] == '\n')
			return (pos + 1);
		pos++;
	}
	return (-1);
}

static char	*ft_read(int fd, char *ret)
{
	char	*buffer;
	int		readvalue;

	readvalue = 1;
	buffer = ft_calloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (readvalue > 0 && ft_getline(buffer) == -1)
	{
		readvalue = read(fd, buffer, BUFFER_SIZE);
		buffer[readvalue] = '\0';
		ret = ft_copy(ret, buffer);
	}
	free(buffer);
	if (ret[0] == '\0')
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

static char	*ft_getdisplayedline(char *buffer)
{
	char	*ret;
	int		nlpos;

	if (!buffer)
		return (NULL);
	nlpos = 0;
	while (buffer[nlpos] && buffer[nlpos] != '\n')
		nlpos++;
	ret = ft_calloc((nlpos + 2));
	if (!ret)
		return (NULL);
	nlpos = 0;
	while (buffer[nlpos] && buffer[nlpos] != '\n')
	{
		ret[nlpos] = buffer[nlpos];
		nlpos++;
	}
	if (buffer[nlpos] == '\n')
		ret[nlpos] = '\n';
	return (ret);
}

static char	*ft_updatebuffer(char *buffer)
{
	int		nlpos;
	int		bufsize;
	int		pos;
	char	*ret;

	nlpos = 0;
	if (!buffer)
		return (NULL);
	bufsize = ft_strlen(buffer);
	nlpos = ft_getline(buffer);
	if (nlpos == -1)
		nlpos = bufsize;
	ret = ft_calloc(((bufsize - nlpos + 1)));
	if (!ret)
		return (NULL);
	pos = 0;
	while (nlpos + pos < bufsize)
	{
		ret[pos] = buffer[nlpos + pos];
		pos++;
	}
	free(buffer);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = ft_calloc(1);
		if (!buffer[fd])
			return (NULL);
	}
	buffer[fd] = ft_read(fd, buffer[fd]);
	line = ft_getdisplayedline(buffer[fd]);
	buffer[fd] = ft_updatebuffer(buffer[fd]);
	return (line);
}
