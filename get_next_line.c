/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:56:21 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/12 23:55:39 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_findnextline(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos] && str[pos] != '\n')
	{
		pos++;
	}
	return (pos);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

char *get_next_line(int fd)
{
	static int	readed;
	int			possave;
	char		*buf;
	char		*printed;
	int			pos;
	
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	possave = readed;
	read(fd, buf, BUFFER_SIZE);
	readed += ft_findnextline(buf);
	printed = malloc(((readed - possave) + 1) * sizeof(char));
	if(!printed)
	{
		free(buf);
		return (NULL);
	}
	pos = 0;
	while ((readed - (possave + pos)) != 0)
	{
		printed[pos] = buf[pos];
		pos++;
	}
	free(buf);
	return (printed);
}

int	main(void)
{
	int	fd;

	fd = open("42", O_RDONLY);
	if(fd == -1)
	{
		ft_putstr("open() error");
		return (0);
	}
	ft_putstr(get_next_line(fd));
	ft_putstr(get_next_line(fd));
	return (0);
}
