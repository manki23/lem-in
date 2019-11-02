/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:52:32 by manki             #+#    #+#             */
/*   Updated: 2019/11/02 17:43:22 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		ft_clean_path(t_all **map)
{
	t_room	*tmp;
	t_room	*end;
	t_room	*start;

	end = ft_get_room(&map[0]->room, CMD_END);
	start = ft_get_room(&map[0]->room, CMD_START);
	tmp = map[0]->room;
	while (tmp)
	{
		if (!tmp->child)
			tmp->child = tmp->old_child;
		tmp = tmp->next;
	}
	tmp = map[0]->room;
	while (tmp)
	{
		if (!ft_end_is_a_child(tmp, end) || !ft_start_is_a_parent(tmp, start))
		{
			tmp->parent = tmp->old_parent;
			tmp->child = tmp->old_child;
		}
		tmp = tmp->next;
	}
}

char		ft_is_in_list(t_queue *list, t_room *room)
{
	t_queue		*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->room->name, room->name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		ft_put_child(t_room **end, t_room **start)
{
	t_room	*tmp;

	tmp = end[0];
	while (tmp && tmp->parent && tmp->parent != start[0])
	{
		tmp->parent->child = tmp;
		tmp = tmp->parent;
	}
	if (tmp->parent == start[0] && tmp == end[0])
		tmp->parent->child = tmp;
	tmp = start[0];
}

void		ft_copy_in_old(t_all **map)
{
	t_room	*tmp;

	tmp = map[0]->room;
	while (tmp)
	{
		if (tmp->parent)
			tmp->old_parent = tmp->parent;
		if (tmp->child)
			tmp->old_child = tmp->child;
		tmp = tmp->next;
	}
}

void		ft_set_map_ptr(t_all **map)
{
	if (map[0]->ant_nb)
		free(map[0]->ant_nb);
	if (map[0]->path_cost)
		free(map[0]->path_cost);
	map[0]->ant_nb = map[0]->old_ant_nb;
	map[0]->path_cost = map[0]->old_path_cost;
	map[0]->old_path_cost = NULL;
	map[0]->old_ant_nb = NULL;
}
