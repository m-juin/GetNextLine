/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:48:35 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/16 14:12:28 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int ft_is_buf_valid(char *buf)
{
	int	pos;

	pos = 0;
	if (buf[0] == '\0')
		return (-1);
	while (buf[pos])
	{
		if (buf[pos] == '\n')
			return (pos + 1);
		pos++;
	}
	return (0);
}

static int	ft_strlen(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos])
		pos++;
	return (pos);
}

/*static int movebuf(char *buf)
{
	int	nlpos;
	int	size;
	int	pos;

	pos = 0;
	size = 0;
	while (buf[size])
	{
		if (buf[size] == '\n')
			nlpos = size;
		size++;
	}
	while (pos <= nlpos && buf[nlpos + pos])
	{
		buf[pos] = buf[nlpos + pos];
		pos++;
	}
	buf[pos] = '\0';
	return (nlpos);
}*/

static void	ft_strjoin(char *s1, char *s2)
{
	char	*tmp;
	int		sizes1;
	int		sizes2;
	int		pos;

	tmp = s1;
	free(s1);
	sizes1 = ft_strlen(tmp);
	sizes2 = ft_strlen(s2);
	s1 = malloc ((sizes1 + sizes2 + 1) * sizeof(char));
	if(!s1)
		return ;
	while (pos <= sizes1 + sizes2)
	{
		if (pos < sizes1)
			s1[pos] = tmp[pos];
		else
			s1[pos] = s2[pos - sizes1];
		pos++;
	}
	s1[pos] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[999][BUFFER_SIZE];
	int			readvalue;
	char		*tmp;

	if (fd <= 0 || fd >= 999)
		return (NULL);
	readvalue = ft_is_buf_valid(buffer[fd]);
	tmp = malloc(1);
	while (readvalue == 0)
	{
		read(fd, buffer[fd], BUFFER_SIZE);
		readvalue = ft_is_buf_valid(buffer[fd]);
		ft_strjoin(tmp, buffer[fd]);
	}
	if (readvalue == -1)
	{
		free(tmp);
		return (NULL);
	}
	else
		return(tmp);
}
