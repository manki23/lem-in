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
	if (size >= ft_queue_len(display))
		return (tmp_q->room);
	while (tmp_q && i < size)
	{
		tmp_q = tmp_q->next;
		i++;
	}
	//ft_printf("chose == %s",tmp_q->room->name);
	return(tmp_q->room);
}

int		calc_nodes(t_room *room)
{
	t_room *tmp;
	int c;

	c = 0;
	tmp = room;
	while (tmp)
	{
		tmp = tmp->child;
		c++; 
	}
	//ft_printf("%d", c);
	return (c);
}

int		total_ants(int *ants, int size)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (i < size)
	{
		res = res + ants[i];
		i++;
	}
	return (res);
}

void	chose_ants(int *ants, int c_ants, int size, t_queue *display)
{
	t_room *tmp;
	t_queue *tmp_q;
	int worst;
	int c;

	c = 0;
	worst = 0;
	int i = 0;
	tmp_q = display;
	tmp = tmp_q->room;
	(void)ants;
	(void)size;
	(void)c_ants;
	ft_printf("display == %d\n",ft_queue_len(display));
	while (i < ft_queue_len(display))
	{
		c = calc_nodes(tmp_q->room);
		if (c >= worst)
			worst = c;
		i++;
		c = 0;
		tmp_q = tmp_q->next;
	}
	tmp_q = display;
	while (c < size)
	{
		ants[c] = 1 + (calc_nodes(tmp_q->room) - worst);
		tmp_q = tmp_q->next;
		c++;
	}
	c = 0;
	while (total_ants(ants, ft_queue_len(display)) != c_ants)
	{
		ants[c]++;
		c++;
		if (c >= size)
			c = 0;
	}
	//ft_printf("ants 0 == %d && ants 1 == %d", ants[0], ants[1]);
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
	ft_printf("nbr foiurmis == %d", ants[j]);
	while (j < ft_queue_len(display))
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
	/*while (c <= c_ants)
	{
		while (k < c)
		{
			while (o <= k)
			{
				if (tmp[i])
				{
					//ft_printf("k == %d", k);
					ft_printf("L%d-%s ", i + 1, tmp[i]->name);
					if (k < ft_queue_len(display))
						ft_printf(" ");
					tmp[i] = tmp[i]->child;
				}
				o++;
				i++;
			}
			o = 0;
			if (j < 1)
				j++;
			k++;
		}
		ft_printf("\n");
		k = 0;
		c++;
		i = 0;
		j = 0;
	}*/
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
	c_ants = display_sol(sol, ants);
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
