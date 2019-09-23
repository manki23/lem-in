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

void			set_next(t_queue **cpy, t_queue **before, t_queue **next)
{
	(*cpy)->next = (*next)->next;
	(*next)->next = *cpy;
	(*before) = *next;
	*next = (*cpy)->next;
}

int				sort(t_queue *cpy, t_queue *before, t_queue *next
							, t_queue **first)
{
	int			i;

	i = 0;
	before = NULL;
	cpy = *first;
	next = cpy->next;
	while (next)
	{
		if (cpy->nodes > cpy->next->nodes)
		{
			i = 1;
			if (before == NULL)
				*first = next;
			else
				before->next = next;
			set_next(&cpy, &before, &next);
		}
		else
		{
			before = cpy;
			cpy = cpy->next;
			next = cpy->next;
		}
	}
	return (i);
}

t_queue        *sort_lst(t_queue *display)
{
	t_queue    *cpy;
	t_queue    *before;
	t_queue    *next;
	t_queue    *first;

	first = display;
	before = NULL;
	cpy = first;
	next = cpy->next;
	while (sort(cpy, before, next, &first));
	return (first);
}

int	check_end(t_room **room, int size)
{
	int i;
	t_room **tmp;
	int c;

	c = 0;
	tmp = room;
	i = 0;
	while (i < size)
	{
		if (tmp[i])
			c++;
		i++;
	}
	if (c > 0)
		return -1;
	return (1);
}

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
	if (tmp_q->ants == 0)
		return (NULL);
	tmp_q->ants = tmp_q->ants - 1;
	//ft_printf("room choice == %s\n",tmp_q->room->name);
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
	//ft_printf("c == %d\n", c);
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

t_queue	*chose_ants(int *ants, int c_ants, int size, t_queue *display)
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

	//ft_printf("display == %d\n",ft_queue_len(display));
	while (i < ft_queue_len(display))
	{
		c = calc_nodes(tmp_q->room);
		tmp_q->nodes = c;
		if (c >= worst)
			worst = c;
		i++;
		c = 0;
		tmp_q = tmp_q->next;
	}
	ft_printf("before sort == %s || nodes == %d\n", display->room->name, display);
	display = sort_lst(display);
	ft_printf("after sort == %s\n", display->room->name);
	tmp_q = display;
	while (tmp_q && c < size)
	{
		ants[c] = 1 + (worst - calc_nodes(tmp_q->room));
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
	tmp_q = display;
	while (tmp_q)
	{
		tmp_q->ants = ants[c];
		c++;
		tmp_q = tmp_q->next;
	}
	//ft_printf("ants 0 == %d  && ants 1 == %d", ants[0], ants[1]);
	return (display);
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
	display = chose_ants(ants, c_ants, ft_queue_len(display), display);
	while (k < c_ants)
	{
		if (i >= ft_queue_len(display))
			i = 0;
		tmp[k] = chose_display(display, i);
		if (tmp[k])
			k++;
		i++;
	}
	i = 0;
	j = 0;
	k = 0;
	int size = ft_queue_len(display);
	int o = 0;
	while (total_ants(ants, ft_queue_len(display)) > 0)
	{
		while (o < size)
		{
			if (ants[j] > 0)
			{
				if (tmp[i])
				{
					ft_printf("L%d-%s ", i + 1, tmp[i]->name, ants[j]);
					tmp[i] = tmp[i]->child;
				}
				i++;
				if (o >= size - ft_queue_len(display))
						ants[j]--;
			}
			if (o >= size - ft_queue_len(display) && j < ft_queue_len(display) - 1)
				j++;
			o++;
		}
		ft_printf("\n");
		i = 0;
		size = size + ft_queue_len(display);
		o = 0;
		j = 0;
	}
	i = 0;
	j = 0;
	k = 0;
	while (check_end(tmp, c_ants) == -1)
	{
		while (i < c_ants)
		{
			if (tmp[i])
			{
				ft_printf("L%d-%s ", i + 1, tmp[i]->name);
				tmp[i] = tmp[i]->child;
			}
			i++;
		}
		ft_printf("\n");
		i = 0;
	}
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
		//sort_sol(sol);
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

void	ft_print_queue(t_queue *queue)
{
	t_queue	*tmp;

	tmp = queue;
	ft_putendl("inside the queue :");
	while (tmp)
	{
		ft_putendl(tmp->room->name);
		tmp = tmp->next;
	}
	ft_putendl("");
}
