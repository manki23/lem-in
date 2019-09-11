/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_breadth_first_search.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:52:25 by manki             #+#    #+#             */
/*   Updated: 2019/09/11 13:35:22 by manki            ###   ########.fr       */
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

void			ft_print_room_ptr(t_room *room)
{
	t_room		*tmp;

	tmp = room;
	while (tmp)
	{
		ft_putendl("-------------------");
		ft_printf("tmp: %s\n", tmp->name);
		if (tmp->parent)
			ft_printf("parent = %s\n", tmp->parent->name);
		if (tmp->child)
			ft_printf("child = %s\n", tmp->child->name);
		if (tmp->old_parent)
			ft_printf("old_parent = %s\n", tmp->old_parent->name);
		if (tmp->old_child)
			ft_printf("old_child = %s\n", tmp->old_child->name);
		tmp = tmp->next;
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
		working_node->room->visit++;
		i = -1;
		while (working_node->room->tab && working_node->room->tab[++i])
		{
			if (working_node->room->tab[i]->visit == 0)
			{
				if (working_node->room->tab[i] != end)
					working_node->room->tab[i]->parent = working_node->room;
				if (working_node->room != start)
					working_node->room->child =working_node->room->tab[i];
				ft_enqueue(&list, &working_node->room->tab[i]);
			}
		}
		free(working_node);
	}
	ft_print_room_ptr(map->room);
	ft_free_queue(&list);
}
