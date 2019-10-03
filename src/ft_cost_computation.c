/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cost_computation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:12:23 by manki             #+#    #+#             */
/*   Updated: 2019/10/03 14:24:15 by manki            ###   ########.fr       */
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
		if ((ants[0] - (1 + tab[0][len - 1] - tab[0][i])) >= 0)
		{
			ant_nb[0][i] += 1 + tab[0][len - 1] - tab[0][i];
			ants[0] -= ant_nb[0][i];
		}
		else
		{
			ant_nb[0][i] = ants[0];
			ants[0] = 0;
		}
	}
}

static int		ft_divide_ants_rest(int **tab, int **nb, int len, int *ant)
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
		return (tab[0][i - 1] + nb[0][i - 1] - 1);
	return (INT_MAX);
}

int				ft_cost_computation(t_all **map, t_queue **sol)
{
	int		*ant_nb;
	int		len;
	int		ants;
	int		final_cost;

	ants = map[0]->ants;
	len = ft_queue_len(*sol);
	map[0]->path_cost = (int *)malloc(sizeof(int) * len);
	ant_nb = (int *)malloc(sizeof(int) * len);
	ft_initialize_tab(&map[0]->path_cost, &ant_nb, sol, len);
	ft_first_ants(len, &ants, &map[0]->path_cost, &ant_nb);
	final_cost = ft_divide_ants_rest(&map[0]->path_cost, &ant_nb, len, &ants);
	return (final_cost);
}
