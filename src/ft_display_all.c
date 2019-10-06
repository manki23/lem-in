/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yodana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:59:53 by yodana            #+#    #+#             */
/*   Updated: 2019/10/06 18:36:33 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_room		**ft_set_ant_tmp(t_queue **sol, t_all *map)
{
	int			i;
	int			j;
	t_queue		*q_tmp;
	t_room		**ant_tmp;

	if (!(ant_tmp = (t_room **)malloc(sizeof(t_room) * map->ants)))
		ft_error("ERROR", 2);
	i = 0;
	int k = 0;
	while (i < map->ants && ++k <= 100)
	{
		q_tmp = sol[0];
		j = 0;
		while (i < map->ants && q_tmp)
		{
			if (map->ant_nb[j] > 0)
			{
				ant_tmp[i] = q_tmp->room;
				i++;
				map->ant_nb[j] -= 1;
			}
			q_tmp = q_tmp->next;
			j++;
		}
	}
	return (ant_tmp);
}

char	ft_ant_already_going_there(t_room **ant_tmp, int index, t_room *end)
{
	int		i;

	i = 0;
	while (i < index)
	{
		if (ant_tmp[i] && ant_tmp[i] == ant_tmp[index] && ant_tmp[index] != end)
			return (1);
		i++;
	}
	return (0);
}

char	ft_no_more_ant_tmp(t_room **ant_tmp, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (ant_tmp[i] != NULL)
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_sol(t_queue **sol, t_all *map, t_room **end)
{
	t_room	**ant_tmp;
	int		i;
	int		j;
	int		k;
	int		space;

	ant_tmp = ft_set_ant_tmp(sol, map);
	k = 0;
	while (!ft_no_more_ant_tmp(ant_tmp, map->ants))
	{
		space = -1;
		i = -1;
		while (++i < map->ants)
		{
			if (ant_tmp[i] && !ft_ant_already_going_there(ant_tmp, i, end[0]))
			{
				if (++space)
					ft_putchar(' ');
				ft_printf("L%d-%s", i + 1, ant_tmp[i]->name);
			}
			else if (ant_tmp[i])
				break;
		}
		j = 0;
		while (j < i)
		{
			if (ant_tmp[j] != NULL)
				ant_tmp[j] = ant_tmp[j]->child;
			j++;
		}
		ft_putendl("");
		k++;
	}
	map->total_of_lines = k;
	free(ant_tmp);
}

void	ft_inside_sol(t_queue *sol)
{
	t_queue *tmp;

	tmp = sol;
	while (tmp)
	{
		ft_printf("path name : %s\n", tmp->room->name);
		ft_printf("path cost : %d\n", ft_solution_len(tmp->room));
		ft_putendl("//////////////");
		tmp = tmp->next;
	}
		ft_putendl("//////////////");
}

void	ft_display_bis(t_queue **sol, t_all *map)
{
	int		i;
	t_room	*end;

	ft_inside_sol(*sol);
//	ft_paths(map, ft_queue_len(*sol));
	end = ft_get_room(&map->room, ft_get_room_pos_by_cmd(map->room, CMD_END));
	if (ft_queue_len(*sol) == 1 && calc_nodes((*sol)->room) == 1)
	{
		i = 0;
		while (++i <= map->ants)
		{
			ft_printf("L%d-%s", i, sol[0]->room->name);
			if (i < map->ants)
				ft_printf(" ");
			i++;
		}
		ft_printf("\n");
		map->total_of_lines++;
	}
	else
		ft_print_sol(sol, map, &end);
}
