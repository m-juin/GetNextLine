/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:01:22 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/16 14:41:09 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

/*static int	ft_findnewline(char *buf)
{
	int	pos;

	pos = 0;
	while (buf[pos])
	{
		if (buf[pos] == '\n')
			return (pos);
		pos++;
	}
	return (-1);
}*/

/*static int	ft_strlen(char *str, int boolean)
{
	int	size;

	size = 0;
	if(!str)
		return (0);
	if (boolean == 0)
		while(str[size])
			size++;
	else
	{
		while (str[size] && str[size] != '\n')
			size++;
		if(str[size] == '\n')
			size++;
	}
	return (size);
}

static char	*ft_join(char *s1, char *s2)
{
	int 	ss1;
	int		ss2;
	int		pos;
	char 	*tmp;

	ss1 = ft_strlen(s1, 1); 
	ss2 = ft_strlen(s2, 1);	
	tmp = malloc((ss1 + ss2 + 1) * sizeof(char));
	if(!tmp)
		return (NULL);
	pos = 0;
	while (pos < ss1 + ss2)
	{
		if (pos < ss1)
			tmp[pos] = tmp[pos];
		else
			tmp[pos] = s2[pos - ss1];
		pos++;
	}
	free(s1);
	tmp[pos] = 0;
	return (tmp);
}

char	*ft_movebuf(char *buf)
{
	int 	value;
	int		fullsize;
	int		pos;
	char	*ret;

	value = ft_strlen(buf, 1);
	ret = malloc((value + 1) * sizeof(char));
	if(!ret)
		return(NULL);
	fullsize = ft_strlen(buf, 0);
	pos = 0;
	while (buf[pos])
	{
		if (pos < value)
			ret[pos] = buf[pos];
		if (pos + value < fullsize)
			buf[pos] = buf[pos + value];
		else
			buf[pos] = '\0';
		pos++;
	}
	buf[pos] = '\0';
	return (ret);
}

char *ft_boucle(char *buf, int fd)
{
	int	readvalue;
	char	*tmp;
	char	*ret;

	readvalue = -1;
	ret = NULL;
	while (readvalue != 0)
	{
		tmp = NULL;
		tmp = ft_movebuf(buf);
		if(!tmp)
			return(NULL);
		ret = ft_join(ret, tmp);
		free(tmp);
		if(!ret)
			return(NULL);
		if(buf[0] != '\0')
			break ;
		readvalue = read(fd, buf, BUFFER_SIZE);
	}
	return (ret);
}*/

int	ft_getline(char *src)
{
	int pos;

	pos = 0;
	while (src[pos])
	{
		if(src[pos] == '\n')
			return (pos + 1);
		pos++;
	}
	return (-1);
}
static int ft_strlen(char *str)
{
	int pos;

	pos = 0;
	while (str[pos])
		pos++;
	return (pos);
	
}

char	*ft_copy(char *dst, char *src)
{
	char	*tmp;
	int		dstpos;
	int		srcpos;
	int		globalpos;

	if (!dst || !src)
		return (NULL);
	dstpos = ft_strlen(dst);
	srcpos = ft_strlen(src);
	tmp = malloc((dstpos + srcpos + 1) * sizeof(char));
	if (!tmp)
		return(NULL);
	globalpos = 0;
	while (globalpos < dstpos + srcpos)
	{
		if (globalpos < srcpos)
			tmp[globalpos] = src[globalpos];
		else
			tmp[globalpos] = src[globalpos - srcpos];
		globalpos++;
	}
	tmp[globalpos] = '\0';
	free(dst);
	return (tmp);
}

char	*ft_read(int fd, char *ret)
{
	char	*buffer;
	int		readvalue;

	readvalue = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (readvalue > 0 && ft_getline(buffer) == -1)
	{
		readvalue = read(fd, buffer, BUFFER_SIZE);
		buffer[readvalue] = '\0';
		ret = ft_copy(ret, buffer);
	}
	free(buffer);
	return (ret);
}

char	*ft_getdisplayedline(char *buffer)
{
	char	*ret;
	int		nlpos;

	if (!buffer[0])
		return (NULL);
	nlpos = 0;
	while (buffer[nlpos] && buffer[nlpos] != '\n')
		nlpos++;
	ret = malloc((nlpos + 1) * sizeof(char));
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

char	*ft_updatebuffer(char *buffer)
{
	int		nlpos;
	int		bufsize;
	int		pos;
	char    *ret;

	nlpos = 0;
	if(!buffer)
		return (NULL);
	bufsize = ft_strlen(buffer);
	while (buffer[nlpos] && buffer[nlpos] != '\n')
		nlpos++;
	ret = malloc(((bufsize - nlpos + 1)) * sizeof(char));
	if (!ret)
		return (NULL);
	pos = 0;
	while (nlpos + pos < bufsize)
	{
		ret[pos] = buffer[nlpos + pos];
		pos++;
	}
	ret[pos] = '\0';
	free(buffer);
	return (ret);
}
char	*get_next_line(int fd)
{
	static char *buffer;
	char	*line;

	if(read(fd,0,0) < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = ft_read(fd, buffer);
	line = ft_getdisplayedline(buffer);
	buffer = ft_updatebuffer(buffer);
	return (line);
}
