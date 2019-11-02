/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:04:47 by manki             #+#    #+#             */
/*   Updated: 2019/11/02 13:11:47 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static char		ft_sol_is_colliding(t_queue *sol, t_room *path, t_room *end)
{
	t_queue		*tmp_sol;
	t_room		*tmp_path;
	t_room		*tmp_room;

	tmp_sol = sol;
	while (tmp_sol)
	{
		tmp_path = path;
		while (tmp_path)
		{
			tmp_room = tmp_sol->room;
			while (tmp_room)
			{
				if (tmp_room == tmp_path && tmp_room != end)
					return (1);
				tmp_room = tmp_room->child;
			}
			tmp_path = tmp_path->child;
		}
		tmp_sol = tmp_sol->next;
	}
	return (0);
}

void	ft_stock_solution(t_queue **sol, t_all **map)
{
	t_room		*tmp;
	t_room		*start;
	t_room		*end;

	start = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_START));
	end = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_END));
	tmp = map[0]->room;
	while (tmp)
	{
		if (((tmp->parent && tmp->parent == start)
				|| (tmp == end && tmp->old_parent == start))
				&& !ft_sol_is_colliding(*sol, tmp, end))
			ft_enqueue(sol, &tmp);
		tmp = tmp->next;
	}
	if (!sol[0] && start->child && start->child == end)
		ft_enqueue(sol, &start);
	ft_sort_queue(sol);
}

int		ft_another_path_exist(t_all *map, t_room **room)
{
	t_room	*start;
	int		i;

	start = ft_get_room(&map->room, ft_get_room_pos_by_cmd(map->room,
				CMD_START));
	i = -1;
	while (room[++i])
		if (room[i]->visit == 0 && room[i]->child == NULL && room[i] != start)
			return (1);
	return (0);
}

void	ft_visit_node(t_room **room, t_all **map, char *stop)
{
	t_room	*end;
	t_room	*start;
	int		i;

	start = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_START));
	end = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_END));
	i = -1;
	while (room[0]->tab && room[0]->tab[++i] && !stop[0])
	{
		if (room[0]->tab[i] == end && !(room[0] == start && start->old_child
					== end && end->old_parent == start))
			stop[0]++;
		if (room[0] != end && !room[0]->tab[i]->parent &&
				room[0]->tab[i] != start && room[0]->parent != room[0]->tab[i])
		{
			room[0]->tab[i]->parent = room[0];
		}
	}
	room[0]->visit++;
}

void	ft_check_duplicates(t_all **map)
{
	t_room	*tmp;

	tmp = map[0]->room;
	while (tmp)
	{
		if (tmp->parent && tmp->old_child && tmp->parent == tmp->old_child)
			tmp->parent = tmp->old_parent;
		if (tmp->child && tmp->old_parent && tmp->child == tmp->old_parent)
			tmp->child = tmp->old_child;
		tmp = tmp->next;
	}
}

int		ft_solution_len(t_room *room)
{
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = room;
	while (tmp)
	{
		i++;
		tmp = tmp->child;
	}
	return (i);
}
