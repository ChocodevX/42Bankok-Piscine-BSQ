/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ponsumri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:20:45 by ponsumri          #+#    #+#             */
/*   Updated: 2026/05/27 15:20:46 by ponsumri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty_char;
	char	obstacle_char;
	char	full_char;
	char	**map;
	int		**dp;
	int		best_size;
	int		best_row;
	int		best_col;
}			t_map;

void		ft_process_map(int fd, t_map *map);
void		ft_process_files(int argc, char **argv, t_map *map);
void		ft_print_map(t_map *map);
void		ft_draw_square(t_map *map);
char		**ft_build_map(char *content, t_map *map);
int			ft_parse_header(char *content, t_map *map);
char		*ft_read_file(int fd);
int			ft_min(int a, int b, int c);
int			**ft_build_dp(t_map *map);
int			ft_atoi(char *str, int len);
int			ft_strlen(char *str);
void		ft_putstr_fd(char *str, int fd);
void		ft_free_map(t_map *map);
int			ft_validate_map(t_map *map);

#endif
