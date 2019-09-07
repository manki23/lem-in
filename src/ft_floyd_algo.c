/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floyd_algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:22:03 by manki             #+#    #+#             */
/*   Updated: 2019/09/07 16:18:42 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		ft_initialize_d(int **mat, int len, t_all *map)
{
	int		i;
	int		j;
	char	*room_a;
	char	*rom_b;

	i = -1;
	while (++i < len)
	{
		room_a = ft_get_room_name(map->room, i + 1);
		j = -1;
		while (++j < len)
		{
			rom_b = ft_get_room_name(map->room, j + 1);
			if (i == j)
				mat[i][j] = 0;
			else if (room_a && rom_b && ft_tube_exist(map->tube, room_a, rom_b))
				mat[i][j] = 1;
			else
				mat[i][j] = INT_MAX;
		}
	}
}

static void		ft_apply_floyd(int **mat_d, int **mat_p, int len)
{
	int		k;
	int		i;
	int		j;

	k = -1;
	while (++k < len)
	{
		i = -1;
		while (++i < len)
		{
			j = -1;
			if (k == i || mat_d[i][k] == INT_MAX)
				j = len;
			while (++j < len)
			{
				if ((mat_d[i][k] != INT_MAX) && (mat_d[k][j] != INT_MAX) &&
						(mat_d[i][j] > mat_d[i][k] + mat_d[k][j]))
				{
					mat_d[i][j] = mat_d[i][k] + mat_d[k][j];
					mat_p[i][j] = k + 1;
				}
			}
		}
	}
}

static char		ft_matrice_is_good(int **mat, t_all *map)
{
	int		room_start;
	int		room_end;

	room_start = ft_get_room_pos_by_cmd(map->room, CMD_START);
	room_end = ft_get_room_pos_by_cmd(map->room, CMD_END);
	if (mat[room_start - 1][room_end - 1] == INT_MAX)
		return (0);
	else
		return (1);
}

char			ft_floyd_algo(t_all *map)
{
	int		**matrice_d;
	int		**matrice_p;
	int		len;

	matrice_d = NULL;
	matrice_p = NULL;
	len = ft_room_lstlen(map->room);
	matrice_d = ft_alloc_matrice(matrice_d, len);
	matrice_p = ft_alloc_matrice(matrice_p, len);
	if (!matrice_d || !matrice_p)
		return (0);
	ft_initialize_d(matrice_d, len, map);
	ft_apply_floyd(matrice_d, matrice_p, len);
//	ft_display_matrice("Matrice D", matrice_d, len);
//	ft_display_matrice("Matrice P", matrice_p, len);
	if (!ft_matrice_is_good(matrice_d, map))
	{
		ft_free_matrice(matrice_d, len);
		ft_free_matrice(matrice_p, len);
		return (0);
	}
	ft_solver(matrice_d, matrice_p, map);
	ft_free_matrice(matrice_d, len);
	ft_free_matrice(matrice_p, len);
	return (1);
}
