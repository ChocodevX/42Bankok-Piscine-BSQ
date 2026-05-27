/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ponsumri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:20:59 by ponsumri          #+#    #+#             */
/*   Updated: 2026/05/27 15:21:00 by ponsumri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	ft_print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		write(1, map->map[i], map->cols);
		write(1, "\n", 1);
		i++;
	}
}

void	ft_draw_square(t_map *map)
{
	int	i;
	int	j;

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
