/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ponsumri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:21:17 by ponsumri          #+#    #+#             */
/*   Updated: 2026/05/27 15:21:22 by ponsumri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static int	ft_fill_row(char **slot, char *content, int *i, int cols)
{
	int	col;

	*slot = malloc(sizeof(char) * (cols + 1));
	if (!*slot)
		return (0);
	col = 0;
	while (col < cols && content[*i] != '\0' && content[*i] != '\n')
	{
		(*slot)[col] = content[*i];
		(*i)++;
		col++;
	}
	(*slot)[col] = '\0';
	if (col < cols || (content[*i] != '\n' && content[*i] != '\0'))
	{
		free(*slot);
		return (0);
	}
	if (content[*i] == '\n')
		(*i)++;
	return (1);
}

static char	**ft_check_end(char **grid, char *content, t_map *map, int i)
{
	int	row;

	grid[map->rows] = NULL;
	if (content[i] == '\0')
		return (grid);
	row = 0;
	while (row < map->rows)
		free(grid[row++]);
	free(grid);
	return (NULL);
}

static char	**ft_fill_rows(char **grid, char *content, t_map *map, int i)
{
	int	row;

	row = 0;
	while (row < map->rows)
	{
		if (content[i] == '\0')
		{
			while (row <= map->rows)
				grid[row++] = NULL;
			return (grid);
		}
		if (!ft_fill_row(&grid[row], content, &i, map->cols))
		{
			while (row > 0)
				free(grid[--row]);
			free(grid);
			return (NULL);
		}
		row++;
	}
	return (ft_check_end(grid, content, map, i));
}

char	**ft_build_map(char *content, t_map *map)
{
	char	**grid;
	int		i;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	i++;
	map->cols = 0;
	while (content[i + map->cols] && content[i + map->cols] != '\n')
		map->cols++;
	grid = malloc(sizeof(char *) * (map->rows + 1));
	if (!grid)
		return (NULL);
	return (ft_fill_rows(grid, content, map, i));
}
