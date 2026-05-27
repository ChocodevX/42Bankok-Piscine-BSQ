/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ponsumri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:21:17 by ponsumri          #+#    #+#             */
/*   Updated: 2026/05/27 15:21:22 by ponsumri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static char	*ft_resize(char *res, int *cs, int n)
{
	char	*new;
	int		i;

	while (cs[1] + n >= cs[0])
		cs[0] *= 2;
	new = malloc(cs[0] + 1);
	if (!new)
	{
		free(res);
		return (NULL);
	}
	i = 0;
	while (i < cs[1])
	{
		new[i] = res[i];
		i++;
	}
	free(res);
	return (new);
}

static char	*ft_grow(char *res, char *buf, int *cs, int n)
{
	int	i;

	if (cs[1] + n >= cs[0])
	{
		res = ft_resize(res, cs, n);
		if (!res)
			return (NULL);
	}
	i = 0;
	while (i < n)
		res[cs[1]++] = buf[i++];
	return (res);
}

char	*ft_read_file(int fd)
{
	char	buf[4096];
	char	*result;
	int		cs[2];
	int		n;

	cs[0] = 4096;
	cs[1] = 0;
	result = malloc(cs[0] + 1);
	if (!result)
		return (NULL);
	n = read(fd, buf, 4096);
	while (n > 0)
	{
		result = ft_grow(result, buf, cs, n);
		if (!result)
			return (NULL);
		n = read(fd, buf, 4096);
	}
	result[cs[1]] = '\0';
	if (n != -1)
		return (result);
	free(result);
	return (NULL);
}

static int	ft_valid_chars(t_map *map)
{
	if ((unsigned char)map->empty_char < 32
		|| (unsigned char)map->empty_char > 126)
		return (0);
	if ((unsigned char)map->obstacle_char < 32
		|| (unsigned char)map->obstacle_char > 126)
		return (0);
	if ((unsigned char)map->full_char < 32
		|| (unsigned char)map->full_char > 126)
		return (0);
	if (map->empty_char == map->obstacle_char)
		return (0);
	if (map->empty_char == map->full_char)
		return (0);
	if (map->obstacle_char == map->full_char)
		return (0);
	return (1);
}

int	ft_parse_header(char *content, t_map *map)
{
	int	i;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (content[i] != '\n' || i < 3)
		return (0);
	map->full_char = content[i - 1];
	map->obstacle_char = content[i - 2];
	map->empty_char = content[i - 3];
	if (!ft_valid_chars(map))
		return (0);
	map->rows = ft_atoi(content, i - 3);
	if (map->rows <= 0)
		return (0);
	return (1);
}
