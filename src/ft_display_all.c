/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:35:59 by manki             #+#    #+#             */
/*   Updated: 2019/09/26 11:28:12 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	print_sol(t_room **tmp, int i)
{
	if (tmp[i])
	{			
		ft_printf("L%d-%s", i + 1, tmp[i]->name);
		tmp[i] = tmp[i]->child;
	}
}

void	first_display(int *ants, t_queue *display, t_room **tmp, int c_ants)
{
	int size;
	int o;
	int i;
	int j;
	int print;

	print = 0;
	size = ft_queue_len(display);
	while (total_ants(ants, ft_queue_len(display)) > 0)
	{
		i = 0;
		o = 0;
		j = 0;
		while (o < size)
		{
			if (ants[j] > 0)
			{
				if (o < size && tmp[i] && print == 1)
					ft_printf(" ");
				if (tmp[i])
					print = 1;
				print_sol(tmp, i);
				i < c_ants - 1 ? i++ : i;
				o >= size - ft_queue_len(display) ? ants[j]-- : ants[j];
			}
			if (o >= size - ft_queue_len(display) && j < ft_queue_len(display) - 1)
				j++;
			o++;
		}
		print = 0;
		ft_printf("\n");
		size = size + ft_queue_len(display);
	}
}

int	sol_one_queue(t_queue *sol)
{
	if (ft_queue_len(sol) == 1)
	{
		if (calc_nodes(sol->room) == 1)
			return (1);
	}
	return (0);
}

void	display_sol(t_queue **display, int c_ants)
{
	int i;
	t_room **tmp;
	int *ants;
	int print;

	print = 0;
	i = 0;
	tmp = (t_room **)malloc(sizeof(t_room *) * (c_ants + 1));
	ants = malloc(sizeof(int*) * ft_queue_len(display[0]));
	chose_ants(ants, c_ants, ft_queue_len(display[0]), &display[0]);
	stock_room_sol(tmp, display[0], c_ants);
	first_display(ants, display[0], tmp, c_ants);
	while (check_end(tmp, c_ants) == -1)
	{
		while (i < c_ants)
		{
			if (tmp[i] && print == 1)
				ft_printf(" ");
			if (tmp[i])
				print = 1;
			print_sol(tmp, i);
			i++;
		}
		print = 0;
		ft_printf("\n");
		i = 0;
	}
	free(tmp);
	free(ants);
}

void	display(t_queue **sol, int ants)
{
	int i;

	i = 1;
	if (sol_one_queue(sol[0]) == 1)
	{
		while (i <= ants)
		{
			ft_printf("L%d-%s", i + 1, sol[0]->room->name);
			if (i < ants)
				ft_printf(" ");
			i++;
		}
		ft_printf("\n");
	}
	else
		display_sol(sol, ants);
}
