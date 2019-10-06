/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cost_computation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:12:23 by manki             #+#    #+#             */
/*   Updated: 2019/10/06 14:42:47 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		ft_initialize_tab(int **tab, int **nb, t_queue **sol, int len)
{
	t_queue	*tmp;
	int		i;

	tmp = sol[0];
	i = -1;
	while (++i < len)
	{
		tab[0][i] = ft_solution_len(tmp->room);
		nb[0][i] = 0;
		tmp = tmp->next;
	}
	ft_sort_integer_table(tab[0], len);
}

static void		ft_first_ants(int len, int *ants, int **tab, int **ant_nb)
{
	int		i;

	i = -1;
	while (ants[0] > 0 && ++i < len)
	{
		ant_nb[0][i] += 1;
		ants[0] -= 1;
	}
	i = -1;
	while (ants[0] > 0 && ++i < len)
	{
		if ((ants[0] - (tab[0][len - 1] - tab[0][i])) >= 0)
		{
			ant_nb[0][i] += tab[0][len - 1] - tab[0][i];
			ants[0] -= tab[0][len - 1] - tab[0][i];
		}
		else
		{
			ant_nb[0][i] += ants[0];
			ants[0] = 0;
		}
	}
}

static int		ft_calc_final_cost(int *path_cost, int *ant_nb, int len)
{
	int		cost;
	int		i;

	cost = -1;
	i = -1;
	while (++i < len)
	{
		if ((path_cost[i] + ant_nb[i] - 1) > cost)
			cost = path_cost[i] + ant_nb[i] - 1;
	}
	return (cost);
}

static int		ft_divide_rest(int **tab, int **nb, int len, int *ant)
{
	int		i;
	int		rest;

	if (len > 0 && ant[0] > 0)
	{
		rest = ant[0] / len;
		i = -1;
		while (++i < len)
			nb[0][i] += rest;
		ant[0] -= rest * len;
		i = -1;
		while (ant[0] > 0 && ++i < len)
		{
			nb[0][i]++;
			ant[0]--;
		}
	}
	i = len;
	while (len > 0 && nb[0][i - 1] == 0)
		i--;
	while ((i - 1) > 0 && tab[0][i - 1] == tab[0][i - 1 - 1])
		i--;
	if (len > 0)
		return (ft_calc_final_cost(tab[0], nb[0], len));
	return (INT_MAX);
}

void			ft_paths(t_all *map, int sol_nb)
{
	int		final_cost;

	final_cost = ft_calc_final_cost(map->path_cost, map->ant_nb, sol_nb);
	ft_printf("ant nb: %d\n", map->ants);
	ft_printf("final_cost = %d\n", final_cost);
	for (int u = 0; u < sol_nb; u++)
	{
		ft_printf("Path[%d]:\n\t\tcost == %d\n\t\tant nb == %d\n", u, map->path_cost[u], map->ant_nb[u]);
	}
	ft_putendl("============================");
}

int				ft_cost_computation(t_all **map, t_queue **sol)
{
	int		l;
	int		ants;
	int		final_cost;

	ants = map[0]->ants;
	l = ft_queue_len(*sol);
	if (map[0]->old_path_cost)
		free(map[0]->old_path_cost);
	if (map[0]->old_ant_nb)
		free(map[0]->old_ant_nb);
	map[0]->old_path_cost = map[0]->path_cost;
	map[0]->old_ant_nb = map[0]->ant_nb;
	map[0]->path_cost = (int *)malloc(sizeof(int) * l);
	map[0]->ant_nb = (int *)malloc(sizeof(int) * l);
	ft_initialize_tab(&map[0]->path_cost, &map[0]->ant_nb, sol, l);
	ft_first_ants(l, &ants, &map[0]->path_cost, &map[0]->ant_nb);
	final_cost = ft_divide_rest(&map[0]->path_cost, &map[0]->ant_nb, l, &ants);
	return (final_cost);
}
