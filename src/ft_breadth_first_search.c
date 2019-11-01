/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_breadth_first_search.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:52:25 by manki             #+#    #+#             */
/*   Updated: 2019/11/01 16:45:50 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*static*/ void		ft_one_backtrack(t_room **room, t_queue **list, int i)
{
	t_room		*tmp;

	room[0]->tab[i]->child = room[0]->tab[i]->old_parent;
	if (room[0]->tab[i]->child->visit == 0)
		ft_enqueue(list, &room[0]->tab[i]->child);
	room[0]->tab[i]->child->parent = room[0]->tab[i];
	room[0]->tab[i]->parent = room[0];
	room[0]->child = room[0]->tab[i];
//	room[0]->tab[i]->visit++;
	room[0]->tab[i]->child->child = NULL;
	tmp = room[0]->tab[i]->child->old_parent;
	while (tmp)
	{
		tmp->child = NULL;
		tmp->parent = NULL;
		tmp = tmp->old_parent;
	}
}

static void		ft_bfs_run(t_queue **list, char *stop, t_all **map)
{
	t_queue		*working_node;
	int			i;

		//	ft_print_queue(*list);
		//	ft_print_room_ptr(map[0]->room);
	working_node = ft_dequeue(list);
//	ft_printf("name : %s | visited : %d\n", working_node->room->name, working_node->room->visit);
	if (working_node->room->visit == 0)
		ft_visit_node(&working_node->room, &map[0], stop);
	i = -1;
	//	ft_putendl("this is a loop");
	while (working_node->room->tab && working_node->room->tab[++i])
	{
	//		ft_printf("working_node->tab[%d] == %s\n", i, working_node->room->tab[i]->name);
		if (working_node->room->tab[i]->visit == 0 &&
				working_node->room->tab[i]->child == NULL
				&& !ft_is_in_list(*list, working_node->room->tab[i]))
			ft_enqueue(list, &working_node->room->tab[i]);
		else if (working_node->room->tab[i]->visit == 0 &&
				working_node->room->tab[i]->child != NULL &&
				!ft_another_path_exist(map[0], working_node->room->tab))
		{
		//	ft_putendl("before ft_one_backtrack:");
		//	ft_printf("working_node == %s\n", working_node->room->name);
		//	ft_print_room_ptr(map[0]->room);
			ft_one_backtrack(&working_node->room, list, i);
		//	ft_putendl("after ft_one_backtrack:");
		//	ft_print_room_ptr(map[0]->room);
		}
	}
	free(working_node);
}

static char		ft_bfs_algo(t_all **map, unsigned long long tour)
{
	t_room		*start;
	t_room		*end;
	t_queue		*list;
	char		stop;

	start = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_START));
	end = ft_get_room(&map[0]->room, ft_get_room_pos_by_cmd(map[0]->room,
				CMD_END));
	list = ft_create_queue(&start);
	stop = 0;
	while (!stop && list)
		ft_bfs_run(&list, &stop, map);
	if (stop || !list)
		ft_put_child(map, &end, &start);
	ft_free_queue(&list);
//	ft_print_room_ptr(map[0]->room);
	if (!end->parent && tour == 0)
		return (0);
	if (end->parent == start)
		end->old_parent = end->parent;
	end->parent = NULL;
	return (1);
}

static void		ft_keep_going(int *k_g, t_queue **sol, int *s_cost, t_all *map)
{
	int			cost;
	t_room		*tmp;

	k_g[0] = 0;
	cost = ft_cost_computation(&map, sol);
	if (cost < s_cost[0])
	{
		s_cost[0] = cost;
		k_g[0] = 1;
		ft_copy_in_old(&map);
	}
	else
	{
		tmp = map->room;
		while (tmp)
		{
			tmp->parent = tmp->old_parent;
			tmp->child = tmp->old_child;
			tmp = tmp->next;
		}
		ft_free_queue(sol);
		ft_stock_solution(sol, &map);
		if (map->ant_nb)
			free(map->ant_nb);
		if (map->path_cost)
			free(map->path_cost);
		map->ant_nb = map->old_ant_nb;
		map->path_cost = map->old_path_cost;
		map->old_path_cost = NULL;
		map->old_ant_nb = NULL;
	}
}

t_queue			*ft_breadth_first_search(t_all *map)
{
	t_queue				*sol;
	int					sol_cost;
	int					keep_going;
	unsigned long long	tour;

	sol = NULL;
	sol_cost = INT_MAX;
	keep_going = 1;
	tour = 0;
	while (keep_going)
	{
		if (!ft_bfs_algo(&map, tour))
			return (NULL);
		ft_reset_visit(&map);
		ft_check_duplicates(&map);
	//	ft_putendl("FINAL:");
	//	ft_print_room_ptr(map->room);
		ft_clean_path(&map);
	//	ft_putendl("FINAL after clean:");
	//	ft_print_room_ptr(map->room);
		ft_stock_solution(&sol, &map);
	//	ft_print_solutions(sol);
		ft_keep_going(&keep_going, &sol, &sol_cost, map);
		if (keep_going)
			ft_free_queue(&sol);
		tour++;
	}
	return (sol);
}
