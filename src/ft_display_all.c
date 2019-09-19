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

t_room	*chose_display(t_queue *display, int size)
{
	t_queue *tmp_q;
	int i;

	i = 0;
	tmp_q = display;
	while (tmp_q && i < size)
	{
		tmp_q = tmp_q->next;
		i++;
	}
	return(tmp_q->room);
}

void	chose_ants(int *ants, int c_ants, int size, t_queue *display)
{
	t_queue *tmp;
	int worst;
	int c;

	c = 0;
	worst = 0;
	tmp = display;
	while (tmp)
	{
		while (tmp->room)
		{
			tmp->room = tmp->child;
			c++;
		}
		if (c >= worst)
			worst = c;
		tmp = tmp->next;
	}
}

int		display_sol(t_queue *display, int c_ants)
{
	int i;
	t_room **tmp;

	i = 0;
	int j;
	j = 0;
	tmp = (t_room **)malloc(sizeof(t_room *) * c_ants);
	int *ants;
	int k;
	k = 0;
	ants = malloc(sizeof(int*) * ft_queue_len(display));
	chose_ants(ants, c_ants, ft_queue_len(display), display);
	/*while (j <= 1)
	{
		while (i < ants[j])
		{
			tmp[k] = chose_display(display, i);
			k++;
			i++;
		}
		i = 0;
		j++;
	}
	i = 0;
	j = 0;
	k = 0;
	int o = 0;
	int c = 0;
	while (c <= 3)
	{
		while (k <= c)
		{
			while (o < ants[j])
			{
				ft_printf("%s ", tmp[i]->name);
				tmp[i] = tmp[i]->child;
				o++;
				i++;
			}
			o = 0;
			if (j <= 1)
				j++;
			k++;
		}
		ft_printf("\n");
		k = 0;
		c++;
		i = 0;
		j = 0;
	}*/
	ft_printf("\n");
	return (c_ants);
}

void	display(t_queue *sol, int ants)
{
	int i;
	t_queue	*display;
	int c_ants;
	(void)ants;
	display = (t_queue *)malloc(sizeof(t_queue) * ft_queue_len(sol) + 1);
	c_ants = 1;
	i = 1;
	ft_printf("sol == %p\n", sol);
//	ft_printf("SOL->name == %s || SOL->name->next %s\n", sol.room->name, sol.next->room->name);
	//while (c_ants <= ants)
	//{
		c_ants = display_sol(sol, ants);
	//	if (c_ants <= ants)
	//	{
			//ft_printf("SOL->name == %s || SOL->name->next %s\n", sol.room->name, sol.next->room->name);
	//		i++;
	//	}
	//}
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
