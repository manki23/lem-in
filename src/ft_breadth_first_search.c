/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_breadth_first_search.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:52:25 by manki             #+#    #+#             */
/*   Updated: 2019/09/16 11:44:11 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

char		ft_all_room_visited(t_room *room)
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

static char		ft_end_is_a_child(t_room *room, t_room *end)
{
	t_room		*tmp;

	tmp = room;
	while (tmp)
	{
		if (tmp == end)
			return (1);
		tmp = tmp->child;
	}
	return (0);
}

void		ft_clean_path(t_all **map)
{
	t_room		*tmp;
	t_room		*end;

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

void			ft_put_child(t_room **room, t_room **start)
{
	t_room		*tmp;

	tmp = room[0];
	while (tmp && tmp->parent && (tmp->parent != start[0]))
	{
		tmp->parent->child = tmp;
		tmp = tmp->parent;
	}
}
void			ft_copy_in_old(t_all **map)
{
	t_room		*tmp;

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

void			ft_stock_solution(t_queue **sol, t_all **map)
{
	t_room		*tmp;
	t_room		*start;

	start = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_START));
	tmp = map[0]->room;
	while (tmp)
	{
		if (tmp->parent && tmp->parent == start)
			ft_enqueue(sol, &tmp);
		tmp = tmp->next;
	}
}

void			ft_reset_visit(t_all **map)
{
	t_room		*tmp;

	tmp = map[0]->room;
	while (tmp)
	{
		tmp->visit = 0;
		tmp = tmp->next;
	}
}

int				ft_another_path_exist(t_room **room)
{
	int		i;

	i = -1;
	while (room[++i])
		if (room[i]->visit == 0 && room[i]->child == NULL)
			return (1);
	return (0);
}

static void		ft_visit_node(t_room **room, t_all **map, char *stop)
{
	t_room		*end;
	int			i;

	end = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_END));
	i = -1;
	while (room[0]->tab && room[0]->tab[++i] && !stop[0])
	{
		if (room[0]->tab[i] == end)
			stop[0]++;
		if (!room[0]->tab[i]->parent)
			room[0]->tab[i]->parent = room[0];
	}
	room[0]->visit++;
}

void		ft_check_duplicates(t_all **map)
{
	t_room		*tmp;

	tmp = map[0]->room;
	while (tmp)
	{
		if (tmp->parent && tmp->old_child && tmp->parent == tmp->old_child)
			tmp->parent = tmp->old_parent;
		if (tmp->child && tmp->old_parent && tmp->child == tmp->old_parent)
			tmp->child = tmp->old_child;
		tmp = tmp->next;
	}
}

int				ft_queue_len(t_queue *queue)
{
	t_queue		*tmp;
	int			i;

	i = 0;
	tmp = queue;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void		ft_swap(int *a, int *b)
{
	int		aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

void			ft_sort_integer_table(int *tab, int size)
{
	int		i;
	int		j;

	j = size - 1;
	while (j > 0)
	{
		i = 0;
		while (i < j)
		{
			if (tab[i] > tab[i + 1])
				ft_swap(&tab[i], &tab[i + 1]);
			i++;
		}
		j--;
	}
}

int				ft_solution_len(t_room *room)
{
	t_room		*tmp;
	int			i;

	i = 0;
	tmp = room;
	while (tmp)
	{
		i++;
		tmp = tmp->child;
	}
	return (i);
}

int				ft_cost_computation(t_all **map, t_queue **sol)
{
	int		*path_cost_tab;
	int		*ant_nb;
	int		len;
	int		i;
	int		ants;
	int		rest;
	int		final_cost;
	t_queue	*tmp;

	ants = map[0]->ants;
	len = ft_queue_len(*sol);
	path_cost_tab = (int *)malloc(sizeof(int) * len);
	ant_nb = (int *)malloc(sizeof(int) * len);
	tmp = sol[0];
	i = -1;
	while (++i < len)
	{
		path_cost_tab[i] = ft_solution_len(tmp->room);
		ant_nb[i] = 0;
		tmp = tmp->next;
	}
	ft_sort_integer_table(path_cost_tab, len);
	i = -1;
	while (ants > 0 && ++i < len)
	{
		if ((ants - (1 + path_cost_tab[len - 1] - path_cost_tab[i])) >= 0)
		{
			ant_nb[i] += 1 + path_cost_tab[len - 1] - path_cost_tab[i];
			ants -= ant_nb[i];
		}
		else
		{
			ant_nb[i] = ants;
			ants = 0;
		}
	}
	if (ants > 0)
	{
		rest = ants / len;
		i = -1;
		while (++i < len)
			ant_nb[i] += rest;
		ants -= rest * len;
		i = -1;
		while (ants > 0 && ++i < len)
		{
			ant_nb[i]++;
			ants--;
		}
	}
//	i = -1;
//	while (++i < len)
//		ft_printf("il y aura %d fourmis dans le chemin %d qui a un cout de %d\n", ant_nb[i], i, path_cost_tab[i]);
	i = len;
	while (ant_nb[i - 1] == 0)
		i--;
	final_cost = path_cost_tab[i - 1] + ant_nb[i - 1] - 1;
//	ft_printf("la solution final aura un cout de %d (lignes)\n", final_cost);
	free(path_cost_tab);
	free(ant_nb);
	return (final_cost);
}

void			ft_breadth_first_search(t_all *map)
{
	t_queue		*list;
	t_room		*start;
	t_room		*end;
	t_queue		*working_node;
	char		stop;
	int			i;
	int			y;
	t_queue		*sol;
	int			sol_cost;
	int			_continue_;

	sol = NULL;
	start = ft_get_room(&map->room, ft_get_room_pos_by_cmd(map->room,
				CMD_START));
	end = ft_get_room(&map->room, ft_get_room_pos_by_cmd(map->room,
				CMD_END));
	y = 0;
	sol_cost = INT_MAX;
	_continue_ = 1;
	while (_continue_)
	{
		list = ft_create_queue(&start);
		stop = 0;
		while (!stop && list)
		{
			working_node = ft_dequeue(&list);
			if (working_node->room->visit == 0)
				ft_visit_node(&working_node->room, &map, &stop);
			i = -1;
			while (working_node->room->tab && working_node->room->tab[++i])
			{
				if (working_node->room->tab[i]->visit == 0 &&
						working_node->room->tab[i]->child == NULL)
					ft_enqueue(&list, &working_node->room->tab[i]);
				else if (working_node->room->tab[i]->visit == 0 &&
						working_node->room->tab[i]->child != NULL &&
						!ft_another_path_exist(working_node->room->tab))
				{
					working_node->room->tab[i]->child =
						working_node->room->tab[i]->old_parent;
					ft_enqueue(&list, &working_node->room->tab[i]->child);
					working_node->room->tab[i]->child->parent =
						working_node->room->tab[i];
					working_node->room->tab[i]->parent =
						working_node->room;
					working_node->room->child = working_node->room->tab[i];
					working_node->room->tab[i]->visit++;
					working_node->room->tab[i]->child->child = NULL;
				}
			}
			if (stop)
				ft_put_child(&end, &start);
			free(working_node);
		}
		ft_free_queue(&list);
		ft_check_duplicates(&map);
		ft_clean_path(&map);
		ft_print_room_ptr(map->room);
		ft_copy_in_old(&map);
		ft_stock_solution(&sol, &map);
		ft_putendl("Solution begin with :");
		ft_print_queue(sol);
		_continue_ = 0;
		i = ft_cost_computation(&map, &sol);
		if (i < sol_cost)
		{
			sol_cost = i;
			_continue_ = 1;
		}
		ft_free_queue(&sol);
		ft_putendl("*********************************************");
		ft_reset_visit(&map);
		end->parent = NULL;
	}
}
