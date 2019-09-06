/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:35:27 by manki             #+#    #+#             */
/*   Updated: 2019/09/06 16:52:36 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static char		ft_room_already_exist(char *room, t_room *list)
{
	t_room	*tmp;
	char	already_exist;

	tmp = list;
	already_exist = 0;
	while (tmp && !already_exist)
	{
		if (!ft_strcmp(tmp->name, room))
			already_exist++;
		tmp = tmp->next;
	}
	return (already_exist);
}

void			ft_print_room_name(t_room *begin)
{
	while (begin)
	{
		ft_printf("name de la room == %s\n", begin->name);
		begin = begin->next;
	}
}

static char		ft_add_room(t_room **list, char **s)
{
	if (!ft_room_already_exist(s[0], *list))
	{
		if (!list[0])
			list[0] = ft_room_lstnew(s[0], ft_atoi(s[1]), ft_atoi(s[2]));
		else
			ft_room_lstadd(list, s[0], ft_atoi(s[1]), ft_atoi(s[2]));
		return (1);
	}
	else
		return (0);
}

char			ft_stock_room(char *input, t_room **list)
{
	char	**split;
	char	ret;

	ret = 0;
	if (!(split = ft_strsplit(input, ' ')))
		return (0);
	ret += ft_add_room(list, split);
	ft_strrdel(split);
	return (ret);
}
