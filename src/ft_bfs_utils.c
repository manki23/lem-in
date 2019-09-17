/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:52:32 by manki             #+#    #+#             */
/*   Updated: 2019/09/16 14:05:34 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static char		ft_end_is_a_child(t_room *room, t_room *end)
{
	t_room	*tmp;

	tmp = room;
	while (tmp)
	{
		if (tmp == end)
			return (1);
		tmp = tmp->child;
	}
	return (0);
}

void			ft_clean_path(t_all **map)
{
	t_room	*tmp;
	t_room	*end;

	end = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_END));
	tmp = map[0]->room;
	while (tmp)
	{
		if (!ft_end_is_a_child(tmp, end))
		{
			tmp->parent = NULL;
			tmp->child = NULL;
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

void			ft_put_child(t_room **room, t_room **start)
{
	t_room	*tmp;

	tmp = room[0];
	while (tmp && tmp->parent && (tmp->parent != start[0]))
	{
		tmp->parent->child = tmp;
		tmp = tmp->parent;
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
