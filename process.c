/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ponsumri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:21:17 by ponsumri          #+#    #+#             */
/*   Updated: 2026/05/27 15:21:22 by ponsumri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static int	ft_setup_map(int fd, t_map *map)
{
	char	*content;

	content = ft_read_file(fd);
	if (!content)
	{
		write(2, "map error1\n", 11);
		return (0);
	}
	if (!ft_parse_header(content, map))
	{
		write(2, "map error2\n", 11);
		free(content);
		return (0);
	}
	map->map = ft_build_map(content, map);
	free(content);
	if (!ft_validate_map(map))
	{
		write(2, "map error3\n", 11);
		ft_free_map(map);
		return (0);
	}
	return (1);
}

void	ft_process_map(int fd, t_map *map)
{
	if (!ft_setup_map(fd, map))
		return ;
	map->dp = ft_build_dp(map);
	if (!map->dp)
	{
		write(2, "map error4\n", 11);
		ft_free_map(map);
		return ;
	}
	ft_draw_square(map);
	ft_print_map(map);
	ft_free_map(map);
}

void	ft_process_files(int argc, char **argv, t_map *map)
{
	int	i;
	int	fd;

	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd == -1)
			write(2, "map error5\n", 11);
		else
		{
			ft_process_map(fd, map);
			close(fd);
		}
		if (i < argc - 1)
			write(1, "\n", 1);
		i++;
	}
}
