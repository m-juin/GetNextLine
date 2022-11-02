/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:01:22 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/24 15:19:23 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	while (readvalue > 0 && buffer != NULL && ft_getline(buffer) == -1)
	{
		readvalue = read(fd, buffer, BUFFER_SIZE);
		if (readvalue == -1)
		{
			free(buffer);
			free(ret);
			return (NULL);
		}
		buffer[readvalue] = '\0';
		ret = ft_copy(ret, buffer);
	}
	if (buffer != NULL)
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
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc(1);
		if (!buffer)
			return (NULL);
	}
	buffer = ft_read(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = ft_getdisplayedline(buffer);
	buffer = ft_updatebuffer(buffer);
	return (line);
}
