/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yodana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:59:53 by yodana            #+#    #+#             */
/*   Updated: 2019/11/02 17:58:26 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		first_display(t_queue *d, t_room **tmp, int c_ants)
{
	int		i;
	int		print;

	print = 0;
	i = 0;
	while (i < c_ants)
	{
		if (already_pass(tmp, i) == -1)
		{
			if (tmp[i] && print == 1)
				ft_printf(" ");
			tmp[i] ? print = 1 : print;
			print_sol(tmp, &i, c_ants);
		}
		else
		{
			tmp_next_child(tmp, i);
			print = 0;
			d->c_t = d->c_t + 1;
			i = 0;
			ft_printf("\n");
		}
	}
	tmp_next_child(tmp, i);
	ft_printf("\n");
}

static void		ft_savelines(t_room ***tmp, int **ants)
{
	free(tmp[0]);
	free(ants[0]);
}

static void		display_sol(t_queue **display, int c_ants, int i, int print)
{
	t_room	**tmp;
	int		*ants;

	if (!(tmp = (t_room **)malloc(sizeof(t_room *) * (c_ants + 1)))
		|| !(ants = malloc(sizeof(int*) * ft_queue_len(display[0]))))
		return ;
	chose_ants(ants, c_ants, ft_queue_len(display[0]), &display[0]);
	stock_room_sol(tmp, display[0], c_ants);
	first_display(display[0], tmp, c_ants);
	while (check_end(tmp, c_ants) == -1)
	{
		while (i < c_ants)
		{
			if (tmp[i] && print == 1)
				ft_printf(" ");
			tmp[i] ? print = 1 : print;
			print_sol(tmp, &i, i + 1);
		}
		print = 0;
		tmp_next_child(tmp, i);
		display[0]->c_t = display[0]->c_t + 1;
		ft_printf("\n");
		i = 0;
	}
	ft_savelines(&tmp, &ants);
}

void			display(t_queue **sol, int ants)
{
	int i;

	i = 1;
	sol[0]->c_t = 0;
	if (ft_queue_len(*sol) == 1 && calc_nodes((*sol)->room) == 1)
	{
		while (i <= ants)
		{
			ft_printf("L%d-%s", i, sol[0]->room->name);
			if (i < ants)
				ft_printf(" ");
			i++;
		}
		ft_printf("\n");
		sol[0]->c_t++;
	}
	else
		display_sol(sol, ants, 0, 0);
}
