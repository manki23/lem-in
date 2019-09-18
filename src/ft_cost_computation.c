/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cost_computation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:12:23 by manki             #+#    #+#             */
/*   Updated: 2019/09/17 15:49:45 by manki            ###   ########.fr       */
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

static int		ft_divide_remaining_ants(int **tab, int **nb, int len, int *ant)
{
	int		i;
	int		rest;

	if (ant[0] > 0)
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
	while (nb[0][i - 1] == 0)
		i--;
	return (tab[0][i - 1] + nb[0][i - 1] - 1);
}

int				ft_cost_computation(t_all **map, t_queue **sol)
{
	int		*path_cost_tab;
	int		*ant_nb;
	int		len;
	int		ants;
	int		final_cost;

	ants = map[0]->ants;
	len = ft_queue_len(*sol);
	path_cost_tab = (int *)malloc(sizeof(int) * len);
	ant_nb = (int *)malloc(sizeof(int) * len);
	ft_initialize_tab(&path_cost_tab, &ant_nb, sol, len);
	ft_first_ants(len, &ants, &path_cost_tab, &ant_nb);
	final_cost = ft_divide_remaining_ants(&path_cost_tab, &ant_nb, len, &ants);
	free(path_cost_tab);
	free(ant_nb);
	return (final_cost);
}
