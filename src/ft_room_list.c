/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:18:34 by manki             #+#    #+#             */
/*   Updated: 2019/09/07 15:19:17 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_room		*ft_room_lstnew(char *name, t_coord c, char cmd)
{
	t_room	*fresh;

	if (!(fresh = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	fresh->name = ft_strdup(name);
	fresh->command = cmd;
	fresh->x = c.x;
	fresh->y = c.y;
	fresh->next = NULL;
	return (fresh);
}

void		ft_room_lstadd(t_room **list, char *name, t_coord c, char cmd)
{
	t_room	*tmp;

	if (*list)
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_room_lstnew(name, c, cmd);
	}
	else
		list[0] = ft_room_lstnew(name, c, cmd);
}

int			ft_room_lstlen(t_room *list)
{
	int		len;
	t_room	*tmp;

	len = 0;
	if (list)
	{
		tmp = list;
		while (tmp)
		{
			tmp = tmp->next;
			len++;
		}
	}
	return (len);
}

char		*ft_get_room_name(t_room *list, int position)
{
	int		i;
	t_room	*tmp;

	i = 0;
	if (list)
	{
		tmp = list;
		while (tmp)
		{
			i++;
			if (i == position)
				return (tmp->name);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

int			ft_get_room_pos_by_cmd(t_room *list, char cmd)
{
	int		i;
	t_room	*tmp;

	i = 0;
	if (list)
	{
		tmp = list;
		while (tmp)
		{
			i++;
			if (tmp->command == cmd)
				return (i);
			tmp = tmp->next;
		}
	}
	return (-1);
}
