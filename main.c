/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ponsumri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:20:52 by ponsumri          #+#    #+#             */
/*   Updated: 2026/05/27 15:20:53 by ponsumri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	main(int argc, char **argv)
{
	t_map	map;

	map = (t_map){0};
	if (argc == 1)
		ft_process_map(0, &map);
	else
		ft_process_files(argc, argv, &map);
	return (0);
}
