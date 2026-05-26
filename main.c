#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

// ##################
#include <stdio.h>

// ##################

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
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(2, "map error\n", 10);
		return (-1);
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		ft_read_file(0);
	else
	{
		int i = 1;
		while (i < argc)
		{
			ft_open_file(argv[i]);
			i++;
		}
	}
}