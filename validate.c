#include "bsq.h"

int	ft_validate_map(t_map *map)
{
	int i;
	int j;

	if (!map->map)
		return (0);
	if (map->rows <= 0 || map->cols <= 0)
		return (0);
	i = 0;
	while (i < map->rows)
	{
		if (!map->map[i])
			return (0);
		j = 0;
		while (map->map[i][j])
			j++;
		if (j != map->cols)
			return (0);
		j = 0;
		while (j < map->cols)
		{
			if (map->map[i][j] != map->empty_char
				&& map->map[i][j] != map->obstacle_char)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}