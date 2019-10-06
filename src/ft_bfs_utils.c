/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:52:32 by manki             #+#    #+#             */
/*   Updated: 2019/10/06 14:42:32 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

char		ft_end_is_a_child(t_room *room, t_room *end)
{
	t_room	*tmp;

	tmp = room;
	while (tmp)
	{
		if (tmp == end)
			return (1);
		if (tmp->child && tmp->child != end && tmp->child->parent != tmp)
			return (0);
		tmp = tmp->child;
	}
	return (0);
}

char		ft_start_is_a_parent(t_room *room, t_room *start)
{
	t_room	*tmp;

	tmp = room;
	while (tmp)
	{
		if (tmp == start)
			return (1);
		if (tmp->parent && tmp->parent != start && tmp->parent->child != tmp)
			return (0);
		tmp = tmp->parent;
	}
	return (0);
}

void			ft_clean_path(t_all **map)
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
		if (!ft_end_is_a_child(tmp, end) || !ft_start_is_a_parent(tmp, start))
		{
			tmp->parent = tmp->old_parent;
			tmp->child = tmp->old_child;
		}
		tmp = tmp->next;
	}
}

void			ft_reset_visit(t_all **map)
{
	t_room	*tmp;

	tmp = map[0]->room;
	while (tmp)
	{
		tmp->visit = 0;
		tmp = tmp->next;
	}
}

static void		ft_forget_this_path(t_room **begin, t_room **start, t_all **map)
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

void			ft_put_child(t_all **map, t_room **end, t_room **start)
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
	while (tmp && tmp->tab && tmp->tab[++i])
	{
		if (tmp->tab[i]->parent && !tmp->tab[i]->child)
			ft_forget_this_path(&tmp->tab[i], start, map);
	}
}

void			ft_copy_in_old(t_all **map)
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
