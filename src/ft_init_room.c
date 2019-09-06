/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:35:27 by manki             #+#    #+#             */
/*   Updated: 2019/09/06 16:33:00 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void			ft_print_room_name(t_room *begin)
{
	while (begin)
	{
		ft_printf("name de la room == %s\n", begin->name);
		begin = begin->next;
	}
}

static void		ft_add_room(t_room **begin, char **s)
{
	if (!begin[0])
		begin[0] = ft_room_lstnew(s[0], ft_atoi(s[1]), ft_atoi(s[2]));
	else
		ft_room_lstadd(begin, s[0], ft_atoi(s[1]), ft_atoi(s[2]));
}

char			ft_stock_room(char *input, t_room **begin)
{
	char	**s;

	if (!(s = ft_strsplit(input, ' ')))
		return (0) ;
	ft_add_room(begin, s);
	ft_strrdel(s);
	return (1);
}
