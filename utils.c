#include "bsq.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

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
	int i;

	if (map->map)
	{
		i = 0;
		while (i < map->rows)
		{
			if (map->map[i])
				free(map->map[i]);
			i++;
		}
		free(map->map);
		map->map = NULL;
	}

	if (map->dp)
	{
		i = 0;
		while (i < map->rows)
		{
			if (map->dp[i])
				free(map->dp[i]);
			i++;
		}
		free(map->dp);
		map->dp = NULL;
	}

	map->rows = 0;
	map->cols = 0;
	map->best_size = 0;
	map->best_row = 0;
	map->best_col = 0;
}