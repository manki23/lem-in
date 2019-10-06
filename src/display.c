/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yodana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:59:53 by yodana            #+#    #+#             */
/*   Updated: 2019/10/03 14:24:31 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	print_sol(t_room **tmp, int *i, int c_ants)
{
	if (tmp[*i])
	{
		ft_printf("L%d-%s", *i + 1, tmp[*i]->name);
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

int		already_pass(t_room **tmp, int i, t_queue **display)
{
	int o;
	t_room *end;
	if (!tmp[i])
		return (-1);
		(void)display;
	end = ft_get_room(&tmp[i], ft_get_room_pos_by_cmd(tmp[i],
				CMD_END));
	//ft_printf("end name == %s ",end->name);
	o = 0;
	while (o < i)
	{
		if (tmp[o] && tmp[i] && tmp[o] == tmp[i] && tmp[i] != end)
			return (1);
		o++;
	}
	return (-1);
}

void	tmp_next_child(t_room **tmp, int i)
{
	int o;

	o = 0;
	while (o < i)
	{
		if (tmp[o])
			tmp[o] = tmp[o]->child;
		o++;
	}
}

void	first_display(int *ants, t_queue *d, t_room **tmp, int c_ants)
{
	int i;
	int print;
	(void)ants;
	print = 0;
	i = 0;
	while (i < c_ants)
	{
		if (already_pass(tmp, i, &d) == -1)
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
		display_sol(sol, ants, 0, 0);
}
