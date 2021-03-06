/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debbug_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 11:07:11 by manki             #+#    #+#             */
/*   Updated: 2019/10/09 11:36:28 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		ft_display_all(t_all *map)
{
	int			i;
	t_room		*room_tmp;

	ft_putendl("---------------------------------");
	ft_printf("Ants number: %d\n", map->ants);
	ft_printf("Rooms: (%d)\n", ft_room_lstlen(map->room));
	room_tmp = map->room;
	while (room_tmp)
	{
		if (room_tmp->command == CMD_START)
			ft_putstr(" (start) ");
		else if (room_tmp->command == CMD_END)
			ft_putstr(" (end) ");
		ft_printf("{%s} has %d connections :\n", room_tmp->name,
				ft_tab_len(room_tmp));
		i = -1;
		while (room_tmp->tab && room_tmp->tab[++i])
			ft_printf("| %s |\n", room_tmp->tab[i]->name);
		ft_putendl("");
		room_tmp = room_tmp->next;
	}
}

void		ft_print_room_ptr(t_room *room)
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
	ft_putendl("***********************************");
}

void		ft_print_solutions(t_queue *list)
{
	t_queue		*tmp;
	t_room		*tmp2;
	int			i;

	tmp = list;
	i = 0;
	while (tmp && ++i)
	{
		ft_printf("solution [%d]:", i);
		tmp2 = tmp->room;
		while (tmp2)
		{
			ft_printf(" %s", tmp2->name);
			if (tmp2->child)
				ft_printf(" ->");
			tmp2 = tmp2->child;
		}
		ft_putendl("");
		tmp = tmp->next;
	}
}

void		ft_print_queue(t_queue *list)
{
	t_queue	*tmp;

	tmp = list;
	ft_putendl("inside the queue :");
	while (tmp)
	{
		ft_putendl(tmp->room->name);
		tmp = tmp->next;
	}
	ft_putendl("");
}

void		ft_paths(t_all *map, int sol_nb)
{
	int		final_cost;
	int		u;

	final_cost = ft_calc_final_cost(map->path_cost, map->ant_nb, sol_nb);
	ft_printf("ant nb: %d\n", map->ants);
	ft_printf("final_cost = %d\n", final_cost);
	u = -1;
	while (++u < sol_nb)
	{
		ft_printf("Path[%d]:\n\t\t", u);
		ft_printf("cost == %d\n\t\t", map->path_cost[u]);
		ft_printf("ant nb == %d\n", map->ant_nb[u]);
	}
	ft_putendl("============================");
}
