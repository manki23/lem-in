/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:01:20 by manki             #+#    #+#             */
/*   Updated: 2019/09/07 16:52:03 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
**static int		ft_tab_min(int *tab, int len)
**{
**	int		i;
**	int		min;
**
**	min = tab[0];
**	i = 0;
**	while (++i < len)
**		if (tab[i] < min)
**			min = tab[i];
**	return (min);
**	}
*/

static void		ft_get_path_bis(int **mat_p, t_all *map, int x, int y)
{
	if (mat_p[x - 1][y - 1] == 0)
		ft_printf("%s <- ", ft_get_room_name(map->room, y));
	else
	{
		ft_get_path_bis(mat_p, map, mat_p[x - 1][y - 1], y);
		ft_get_path_bis(mat_p, map, x,  mat_p[x - 1][y - 1]);
	}
}

static void		ft_get_path(int **mat_p, t_all *map, t_coord c)
{
	ft_putstr("end <- ");
	ft_get_path_bis(mat_p, map, c.x, c.y);
	ft_printf("%s <- ", ft_get_room_name(map->room, c.x));
	ft_putendl("start.");
}

static void		ft_print_path(int **mat_d, int **mat_p, t_all *map)
{
	t_coord	c;
	int		room_start;
	int		room_end;

	room_start = ft_get_room_pos_by_cmd(map->room, CMD_START);
	room_end = ft_get_room_pos_by_cmd(map->room, CMD_END);
	c.x = room_start;
	c.y = room_end;
	ft_printf("Shortest path length : %d\n", mat_d[c.x - 1][c.y - 1]);
	ft_get_path(mat_p, map, c);
}

void			ft_solver(int **mat_d, int **mat_p, t_all *map)
{
	ft_print_path(mat_d, mat_p, map);
}
