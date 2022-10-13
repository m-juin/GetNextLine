/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:56:21 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/14 00:07:32 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

char *get_next_line(int fd)
{
	char 	*buffer;
	char	tmp[1];
	int		readvalue;
	int	pos;

	pos = 0;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!buffer)
		return (NULL);
	while (pos < BUFFER_SIZE)
	{
		readvalue = read(fd, tmp, 1);
		if(readvalue == 0)
			return (NULL);
		buffer[pos] = tmp[0];
		if (buffer[pos] == '\n')
			break ;
		pos++;
	}
	buffer[pos + 1] = 0;
	return (buffer);
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
	ft_putstr(get_next_line(fd));
	ft_putstr(get_next_line(fd));
	ft_putstr(get_next_line(fd));
	ft_putstr(get_next_line(fd));
	return (0);
}
