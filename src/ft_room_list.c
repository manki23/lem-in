/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:18:34 by manki             #+#    #+#             */
/*   Updated: 2019/11/02 17:19:22 by manki            ###   ########.fr       */
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
	fresh->visit = 0;
	fresh->x = c.x;
	fresh->y = c.y;
	fresh->tab = NULL;
	fresh->next = NULL;
	fresh->parent = NULL;
	fresh->child = NULL;
	fresh->old_parent = NULL;
	fresh->old_child = NULL;
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

t_room		*ft_get_room(t_room **list, char cmd)
{
	t_room	*tmp;

	if (*list)
	{
		tmp = *list;
		while (tmp)
		{
			if (tmp->command == cmd)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}
