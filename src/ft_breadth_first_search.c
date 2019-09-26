/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_breadth_first_search.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:52:25 by manki             #+#    #+#             */
/*   Updated: 2019/09/26 11:50:46 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		ft_one_backtrack(t_room **room, t_queue **list, int i)
{
	room[0]->tab[i]->child = room[0]->tab[i]->old_parent;
	ft_enqueue(list, &room[0]->tab[i]->child);
	room[0]->tab[i]->child->parent = room[0]->tab[i];
	room[0]->tab[i]->parent = room[0];
	room[0]->child = room[0]->tab[i];
	room[0]->tab[i]->visit++;
	room[0]->tab[i]->child->child = NULL;
}

static void		ft_bfs_run(t_queue **list, char *stop, t_all **map)
{
	t_queue		*working_node;
	int			i;

	working_node = ft_dequeue(list);
	if (working_node->room->visit == 0)
		ft_visit_node(&working_node->room, &map[0], stop);
	i = -1;
	while (working_node->room->tab && working_node->room->tab[++i])
	{
		if (working_node->room->tab[i]->visit == 0 &&
				working_node->room->tab[i]->child == NULL)
			ft_enqueue(list, &working_node->room->tab[i]);
		else if (working_node->room->tab[i]->visit == 0 &&
				working_node->room->tab[i]->child != NULL &&
				!ft_another_path_exist(working_node->room->tab))
			ft_one_backtrack(&working_node->room, list, i);
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
	{
		ft_bfs_run(&list, &stop, map);
		if (stop)
			ft_put_child(&end, &start);
	}
	ft_free_queue(&list);
	if (!end->parent && tour == 0)
		return (0);
	if (end->parent == start)
		end->old_parent = end->parent;
	end->parent = NULL;
	return (1);
}

static void		ft_keep_going(int *k_g, t_queue **sol, int *s_cost, t_all *map)
{
	int			i;
	t_room		*tmp;

	k_g[0] = 0;
	i = ft_cost_computation(&map, sol);
	if (i < s_cost[0])
	{
		s_cost[0] = i;
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
		ft_check_duplicates(&map);
		ft_clean_path(&map);
		ft_stock_solution(&sol, &map);
		ft_keep_going(&keep_going, &sol, &sol_cost, map);
		if (keep_going)
			ft_free_queue(&sol);
		ft_reset_visit(&map);
		tour++;
	}
	return (sol);
}
