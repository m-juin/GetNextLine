/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:08:03 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/16 14:20:30 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

char	*get_next_line(int fd);

int	main(int ac, char **av)
{
	ac = ac;
	av = av;
	int fd = open("files/nl", O_RDONLY);
	if (fd == -1)
		printf("Error\n");
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
}
