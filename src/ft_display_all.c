/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yodana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:59:53 by yodana            #+#    #+#             */
/*   Updated: 2019/10/02 12:30:37 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	print_sol(t_room **tmp, int *i, int c_ants)
{
	if (tmp[*i])
	{
		ft_printf("L%d-%s", *i + 1, tmp[*i]->name);
		tmp[*i] = tmp[*i]->child;
	}
	if (*i < c_ants)
		*i = *i + 1;
}

int		first_display_check(int o, int size, t_room **tmp, t_queue *d)
{
	if (o < size && tmp[0] && d->print == 1)
		ft_printf(" ");
	tmp[0] ? d->print = 1 : d->print;
	if (o == 0)
		d->c_t++;
	return (1);
}

void	first_display(int *ants, t_queue *d, t_room **tmp, int c_ants)
{
	int size;
	int o;
	int i;
	int j;

	size = ft_queue_len(d);
	while (total_ants(ants, ft_queue_len(d)) > 0)
	{
		i = 0;
		o = -1;
		j = 0;
		while (++o < size)
		{
			if (ants[j] > 0 && first_display_check(o, size, &tmp[i], d) == 1)
			{
				print_sol(tmp, &i, c_ants);
				o >= size - ft_queue_len(d) ? ants[j]-- : ants[j];
			}
			if (o >= size - ft_queue_len(d) && j < ft_queue_len(d) - 1)
				j++;
		}
		d->print = 0;
		ft_printf("\n");
		size = size + ft_queue_len(d);
	}
}

void	display_sol(t_queue **display, int c_ants, int i, int print)
{
	t_room	**tmp;
	int		*ants;
	if (!(tmp = (t_room **)malloc(sizeof(t_room *) * (c_ants + 1))))
		return ;
	if (!(ants = malloc(sizeof(int*) * ft_queue_len(display[0]))))
		return ;
	chose_ants(ants, c_ants, ft_queue_len(display[0]), &display[0]);
	stock_room_sol(tmp, display[0], c_ants);
	first_display(ants, display[0], tmp, c_ants);
	while (check_end(tmp, c_ants) == -1 && 	display[0]->c_t++)
	{
		while (++i < c_ants)
		{
			if (tmp[i] && print == 1)
				ft_printf(" ");
			tmp[i] ? print = 1 : print;
			print_sol(tmp, &i, i - 1);
		}
		print = 0;
		ft_printf("\n");
		i = -1;
	}
	free(tmp);
	free(ants);
}

void	display(t_queue **sol, int ants)
{
	int i;

	i = 1;
	sol[0]->print = 0;
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
		display_sol(sol, ants, -1, 0);
}
