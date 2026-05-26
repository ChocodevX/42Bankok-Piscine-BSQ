#include "bsq.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_find_square(t_map *map, int **dp)
{
	int	i;
	int	j;
	int	best_size;
	int	best_row;
	int	best_col;

	best_size = 0;
	best_row = 0;
	best_col = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (dp[i][j] > best_size)
			{
				best_size = dp[i][j];
				best_row = i;
				best_col = j;
			}
			j++;
		}
		i++;
	}
	map->best_size = best_size;
	map->best_row = best_row - best_size + 1;
	map->best_col = best_col - best_size + 1;
}

int	ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= c)
		return (b);
	return (c);
}

int	**ft_build_dp(t_map *map)
{
	int **dp;
	int i;
	int j;

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
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->map[i][j] == map->obstacle_char)
				dp[i][j] = 0;
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
			else
				dp[i][j] = ft_min(dp[i - 1][j],
									dp[i][j - 1],
									dp[i - 1][j - 1]) +
					1;
			j++;
		}
		i++;
	}
	return (dp);
}