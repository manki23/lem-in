/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_tube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:11:01 by manki             #+#    #+#             */
/*   Updated: 2019/09/06 16:52:45 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static char		ft_both_are_room(char **split, t_room *list)
{
	char	room_a;
	char	room_b;
	t_room	*tmp;

	room_a = 0;
	room_b = 0;
	tmp = list;
	while (tmp)
	{
		if (!ft_strcmp(split[0], tmp->name) && !room_a)
			room_a++;
		else if (!ft_strcmp(split[1], tmp->name) && !room_b)
			room_b++;
		tmp = tmp->next;
	}
	return (room_a && room_b);
}

static char		ft_cmp(char *str1, char *str2, char *ref1, char *ref2)
{
	if (!ft_strcmp(str1, ref1) && !ft_strcmp(str2, ref2))
		return (1);
	else if (!ft_strcmp(str1, ref2) && !ft_strcmp(str2, ref1))
		return (1);
	else
		return (0);
}

static char		ft_tube_already_exist(char *room1, char *room2, t_tube *list)
{
	t_tube		*tmp;
	char		already_exist;

	tmp = list;
	already_exist = 0;
	while (tmp && !already_exist)
	{
		already_exist += ft_cmp(room1, room2, tmp->room_a, tmp->room_b);
		tmp = tmp->next;
	}
	return (already_exist);
}

static char		ft_add_tube(char **split, t_tube **list)
{
	if (!ft_tube_already_exist(split[0], split[1], list[0]))
	{
		if (!list[0])
			list[0] = ft_tube_lstnew(split[0], split[1]);
		else
			ft_tube_lstadd(list, split[0], split[1]);
		return (1);
	}
	else
		return (0);
}

char			ft_stock_tube(char *input, t_all **map)
{
	char	**split;
	char	ret;

	ret = 0;
	if (!(split = ft_strsplit(input, '-')))
		return (0);
	if (ft_both_are_room(split, map[0]->room))
	{
		ft_add_tube(split, &map[0]->tube);
		ret = 1;
	}
	ft_strrdel(split);
	return (ret);
}
