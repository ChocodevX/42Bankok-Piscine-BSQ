/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ponsumri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:21:31 by ponsumri          #+#    #+#             */
/*   Updated: 2026/05/27 15:21:32 by ponsumri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= c)
		return (b);
	return (c);
}

static int	**ft_alloc_dp(t_map *map)
{
	int	**dp;
	int	i;

	dp = malloc(sizeof(int *) * map->rows);
	if (!dp)
		return (NULL);
	i = 0;
	while (i < map->rows)
	{
		dp[i] = malloc(sizeof(int) * map->cols);
		if (!dp[i])
		{
			while (i > 0)
				free(dp[--i]);
			free(dp);
			return (NULL);
		}
		i++;
	}
	return (dp);
}

static void	ft_compute_dp(t_map *map, int **dp, int i, int j)
{
	if (map->map[i][j] == map->obstacle_char)
		dp[i][j] = 0;
	else if (i == 0 || j == 0)
		dp[i][j] = 1;
	else
		dp[i][j] = ft_min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;
	if (dp[i][j] > map->best_size)
	{
		map->best_size = dp[i][j];
		map->best_row = i - dp[i][j] + 1;
		map->best_col = j - dp[i][j] + 1;
	}
}

static void	ft_fill_dp(t_map *map, int **dp)
{
	int	i;
	int	j;

	map->best_size = 0;
	map->best_row = 0;
	map->best_col = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			ft_compute_dp(map, dp, i, j);
			j++;
		}
		i++;
	}
}

int	**ft_build_dp(t_map *map)
{
	int	**dp;

	dp = ft_alloc_dp(map);
	if (!dp)
		return (NULL);
	ft_fill_dp(map, dp);
	return (dp);
}
