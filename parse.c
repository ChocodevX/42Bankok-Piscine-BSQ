#include "bsq.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	**ft_build_map(char *content, t_map *map)
{
	char	**grid;
	int		i;
	int		row;
	int		col;

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
	row = 0;
	while (row < map->rows)
	{
		if (content[i] == '\0')
		{
			grid[row] = NULL;
			return (grid);
		}
		grid[row] = malloc(sizeof(char) * (map->cols + 1));
		if (!grid[row])
			return (NULL);
		col = 0;
		while (col < map->cols)
		{
			grid[row][col] = content[i];
			i++;
			col++;
		}
		grid[row][col] = '\0';
		if (content[i] == '\n')
			i++;
		row++;
	}
	grid[row] = NULL;
	return (grid);
}

int	ft_parse_header(char *content, t_map *map)
{
	int	i;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (content[i] != '\n')
		return (0);
	map->full_char = content[i - 1];
	map->obstacle_char = content[i - 2];
	map->empty_char = content[i - 3];
	map->rows = ft_atoi(content, i - 3);
	if (map->rows <= 0)
		return (0);
	if (map->empty_char == map->obstacle_char)
		return (0);
	if (map->empty_char == map->full_char)
		return (0);
	if (map->obstacle_char == map->full_char)
		return (0);
	return (1);
}

char	*ft_join(char *result, char *buffer, int bytes_read)
{
	char	*new;
	int		old_len;
	int		i;
	int		j;

	old_len = 0;
	if (result)
		while (result[old_len])
			old_len++;
	new = malloc(old_len + bytes_read + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < old_len)
	{
		new[i] = result[i];
		i++;
	}
	j = 0;
	while (j < bytes_read)
	{
		new[i] = buffer[j];
		i++;
		j++;
	}
	new[i] = '\0';
	if (result)
		free(result);
	return (new);
}

char	*ft_read_file(int fd)
{
	char	buffer[4096];
	char	*result;
	int		bytes_read;

	result = NULL;
	while ((bytes_read = read(fd, buffer, 4096)) > 0)
	{
		result = ft_join(result, buffer, bytes_read);
		if (!result)
			return (NULL);
	}
	if (bytes_read == -1)
	{
		if (result)
			free(result);
		return (NULL);
	}
	return (result);
}

int	ft_open_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(2, "map error\n", 10);
		return (-1);
	}
	return (fd);
}