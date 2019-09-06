/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:35:59 by manki             #+#    #+#             */
/*   Updated: 2019/09/06 15:45:04 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	ft_display_all(t_all *map)
{
	t_tube	*tube_tmp;
	t_room	*room_tmp;

	ft_putendl("---------------------------------");
	ft_printf("Ants number: %d\nRooms:\n", map->ants);
	room_tmp = map->room;
	while (room_tmp)
	{
		ft_printf("%s\n", room_tmp->name);
		room_tmp = room_tmp->next;
	}
	ft_putendl("Tubes:");
	tube_tmp = map->tube;
	while (tube_tmp)
	{
		ft_printf("%s - %s\n", tube_tmp->room_a, tube_tmp->room_b);
		tube_tmp = tube_tmp->next;
	}
}