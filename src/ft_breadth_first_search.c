/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_breadth_first_search.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:52:25 by manki             #+#    #+#             */
/*   Updated: 2019/09/09 17:33:45 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static char		ft_all_room_visited(t_room *room)
{
	t_room		*tmp;

	tmp = room;
	while (tmp)
	{
		if (!tmp->visit)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static void		ft_visit(t_room **working_node)
{
	if (working_node[0]->visit == 0)
	{
		ft_putendl(working_node[0]->name);
		working_node[0]->visit++;
	}
}

void			ft_breadth_first_search(t_all *map)
{
	t_queue		*list;
	t_room		*start;
	t_room		*end;
	t_queue		*working_node;
	int			i;

	start = ft_get_room(&map->room, ft_get_room_pos_by_cmd(map->room,
				CMD_START));
	end = ft_get_room(&map->room, ft_get_room_pos_by_cmd(map->room, CMD_END));
	list = ft_create_queue(&start);
	while (!ft_all_room_visited(map->room))
	{
		working_node = ft_dequeue(&list);
		ft_visit(&working_node->room);
		i = -1;
		while (working_node->room->tab && working_node->room->tab[++i])
		{
			ft_visit(&working_node->room->tab[i]);
			ft_enqueue(&list, &working_node->room->tab[i]);
		}
		free(working_node);
	}
	ft_free_queue(&list);
}
