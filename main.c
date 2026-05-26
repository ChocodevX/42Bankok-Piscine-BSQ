#include "bsq.h"

void	ft_process_map(int fd, t_map *map)
{
	char	*content;

	content = ft_read_file(fd);
	if (!content)
	{
		write(2, "map error1\n", 11);
		return ;
	}
	if (!ft_parse_header(content, map))
	{
		write(2, "map error2\n", 11);
		free(content);
		return ;
	}
	map->map = ft_build_map(content, map);
	free(content);
	if (!ft_validate_map(map))
	{
		write(2, "map error3\n", 11);
		ft_free_map(map);
		return ;
	}
	map->dp = ft_build_dp(map);
	if (!map->dp)
	{
		write(2, "map error4\n", 11);
		ft_free_map(map);
		return ;
	}
	ft_find_square(map, map->dp);
	ft_draw_square(map);
	ft_print_map(map);
	ft_free_map(map);
}

int	main(int argc, char **argv)
{
	int i;
	int fd;
	t_map map = {0};

	if (argc == 1)
	{
		ft_process_map(0, &map);
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			if (fd == -1)
			{
				write(2, "map error5\n", 11);
			}
			else
			{
				ft_process_map(fd, &map);
				close(fd);
			}
			if (i < argc - 1)
				write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}