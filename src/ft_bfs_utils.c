/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:52:32 by manki             #+#    #+#             */
/*   Updated: 2019/11/02 12:19:54 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		ft_clean_path(t_all **map)
{
	t_room	*tmp;
	t_room	*end;
	t_room	*start;

	end = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_END));
	start = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_START));
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

char	ft_is_in_list(t_queue *list, t_room *room)
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

void	ft_forget_this_path(t_room **begin, t_room **start, t_all **map)
{
	t_room		*tmp;
	t_room		*tmp2;

	ft_reset_visit(map);
	tmp = begin[0];
	while (tmp && tmp != start[0] && !tmp->visit)
	{
		tmp2 = tmp->parent;
		tmp->parent = tmp->old_parent;
		tmp->child = tmp->old_child;
		tmp->visit++;
		tmp = tmp2;
	}
}

void		ft_put_child(t_all **map, t_room **end, t_room **start)
{
	t_room	*tmp;
	int		i;

	tmp = end[0];
	while (tmp && tmp->parent && tmp->parent != start[0])
	{
		tmp->parent->child = tmp;
		tmp = tmp->parent;
	}
	if (tmp->parent == start[0] && tmp == end[0])
		tmp->parent->child = tmp;
	tmp = start[0];
	i = -1;
	(void)map;
//	while (tmp && tmp->tab && tmp->tab[++i])
//	{
//		if (tmp->tab[i]->parent && !tmp->tab[i]->child && tmp->tab[i] != end[0]
//		&& tmp->tab[i] != start[0])
//			ft_forget_this_path(&tmp->tab[i], start, map);
//	}
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
