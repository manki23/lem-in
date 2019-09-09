/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:18:34 by manki             #+#    #+#             */
/*   Updated: 2019/09/09 14:05:46 by manki            ###   ########.fr       */
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
	fresh->prec = NULL;
	fresh->next = NULL;
	fresh->old_prec = NULL;
	fresh->old_next = NULL;
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

t_room		*ft_get_room(t_room **list, int position)
{
	int		i;
	t_room	*tmp;

	if (*list)
	{
		tmp = *list;
		i = 0;
		while (tmp)
		{
			i++;
			if (i == position)
				return (tmp);
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
