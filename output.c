#include "bsq.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map[i][j])
			j++;
		write(1, map->map[i], j);
		write(1, "\n", 1);
		i++;
	}
}

void	ft_draw_square(t_map *map)
{
	int i;
	int j;

	i = map->best_row;
	while (i < map->best_row + map->best_size)
	{
		j = map->best_col;
		while (j < map->best_col + map->best_size)
		{
			map->map[i][j] = map->full_char;
			j++;
		}
		i++;
	}
}