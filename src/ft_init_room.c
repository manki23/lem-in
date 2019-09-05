/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:35:27 by manki             #+#    #+#             */
/*   Updated: 2019/09/05 14:36:43 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	ft_print_room_name(t_room *begin)
{
	while (begin)
	{
		ft_printf("name de la room == %s\n", begin->name);
		begin = begin->next;
	}
}

void	ft_add_room(t_room **begin, t_room *new)
{
	t_room	*tmp;

	if (new)
	{
		tmp = *begin;
		if (tmp == NULL)
			*begin = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

void	ft_stock_room(char *input, t_room **begin)
{
	char	**s;
	int		i;
	t_room	*room;

	i = 0;
	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return ;
	if (!(s = ft_strsplit(input, ' ')))
		return ;
	if (!(room->name = ft_strdup(s[0])))
		return ;
	room->x = ft_atoi(s[1]);
	room->y = ft_atoi(s[2]);
	room->next = NULL;
	ft_add_room(begin, room);
	ft_strrdel(s);
}
