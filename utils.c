/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ponsumri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:21:40 by ponsumri          #+#    #+#             */
/*   Updated: 2026/05/27 15:21:41 by ponsumri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	ft_atoi(char *str, int len)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	write(fd, str, len);
}

void	ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map && i < map->rows)
		free(map->map[i++]);
	if (map->map)
		free(map->map);
	map->map = NULL;
	i = 0;
	while (map->dp && i < map->rows)
		free(map->dp[i++]);
	if (map->dp)
		free(map->dp);
	map->dp = NULL;
	map->rows = 0;
	map->cols = 0;
	map->best_size = 0;
	map->best_row = 0;
	map->best_col = 0;
}
