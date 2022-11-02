/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:22:27 by mjuin             #+#    #+#             */
/*   Updated: 2022/10/24 15:16:40 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(int size)
{
	char	*ret;
	int		pos;

	pos = 0;
	if (size < 0)
		return (NULL);
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

int	ft_strlen(char *str)
{
	int	pos;

	pos = 0;
	if (!str)
		return (0);
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
	tmp = ft_calloc((dstpos + srcpos + 1));
	if (!tmp)
		return (NULL);
	globalpos = 0;
	while (globalpos < dstpos + srcpos)
	{
		if (globalpos < dstpos)
			tmp[globalpos] = dst[globalpos];
		else
			tmp[globalpos] = src[globalpos - dstpos];
		globalpos++;
	}
	free(dst);
	return (tmp);
}
