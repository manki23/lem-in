/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:26:17 by manki             #+#    #+#             */
/*   Updated: 2019/09/07 11:22:28 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	free_all(t_all *all)
{
	t_tube	*tmp1;
	t_room	*tmp2;
	t_tube	*tube_ref;
	t_room	*room_ref;

	tube_ref = all->tube;
	room_ref = all->room;
	while (tube_ref)
	{
		ft_strdel(&(tube_ref->room_a));
		ft_strdel(&(tube_ref->room_b));
		tmp1 = tube_ref->next;
		free(tube_ref);
		tube_ref = tmp1;
	}
	while (room_ref)
	{
		ft_strdel(&(room_ref->name));
		tmp2 = room_ref->next;
		free(room_ref);
		room_ref = tmp2;
	}
	ft_strdel(&all->command_stack);
}
