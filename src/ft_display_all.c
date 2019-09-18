/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:35:59 by manki             #+#    #+#             */
/*   Updated: 2019/09/18 12:56:40 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*void	check_end(t_queue *display, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (display[i].room->command == CMD_END)
			display[i].room->command = FINISH;
		i++;
	}
}*/

int		display_sol(t_queue *display, int c_ants, int size)
{
	int i;
	int j;

	t_queue tmp;
	j = 0;
	i = 0;
	int k = 0;
	(void)tmp;
	while (i < size)
	{
		ft_printf("display %d == %p", i, display[i]);
		tmp = display[i];
		while (j < 2)
		{
			ft_printf(" L%d-%s for %d ", c_ants, tmp.room->name, i);
			if (j < 1)
				tmp = *(tmp.next);
			c_ants++;
			j++;
		}
		j = 0;
		tmp = display[i];
		display[i].room[k] = *(tmp.room->child);
		k++;
		while (j < 2)
		{
			//ft_printf(" pointeur sur tmp room == %p\n", tmp);
			//ft_printf("\nroom=>name == %s \n",tmp->room->name);
			if (j < 1)
				tmp = *(tmp.next);
			display[i].room[k] = *(tmp.room->child);
			k++;
			//display[i].room = display[i].room->child;
			//display[i] = *display[i].next;
			j++;
		}
		j = 0;
		i++;
	}
	ft_printf("\n");
	return (c_ants);
}

void	display(t_queue sol, int ants)
{
	int i;
	t_queue	*display;
	int c_ants;
	(void)ants;

	display = (t_queue *)malloc(sizeof(t_queue*) * ft_queue_len(&sol) + 1);
	c_ants = 1;
	i = 1;
	display[0] = sol;
	ft_printf("display 0 == %p || sol == %p\n", display[0], sol);
	ft_printf("display->name == %s\n", display[0].room->name);
	//display[1] = sol;
	//ft_printf("display 1  == %p\n", display[1]);
	//display[1] = NULL;
	while (c_ants <= ants)
	{
		c_ants = display_sol(display, 1, i);
		if (c_ants <= ants)
		{
			display[i] = sol;
		//	ft_printf("SOL->name == %s || SOL->name->next %s\n", sol.room->name, sol.next->room->name);
		//	ft_printf("display %d == %p || sol == %p\n", i, display[i], sol);
		//	ft_printf("c_ants == %d\n", c_ants);
			//display[i + 1] = NULL;
			i++;
		}
	}
	//while (check_end(display, i))
	//{
	//	c_ants = display_sol(display, 1, i + 1);
	//}
}

void	ft_display_all(t_all *map)
{
	int		i;
	t_room	*room_tmp;

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

void	ft_print_room_ptr(t_room *room)
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

void	ft_print_queue(t_queue *list)
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
