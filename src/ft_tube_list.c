/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tube_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:19:25 by manki             #+#    #+#             */
/*   Updated: 2019/09/06 16:20:04 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_tube	*ft_tube_lstnew(char *room_a, char *room_b)
{
	t_tube	*fresh;

	if (!(fresh = (t_tube *)malloc(sizeof(t_tube))))
		return (NULL);
	fresh->room_a = ft_strdup(room_a);
	fresh->room_b = ft_strdup(room_b);
	fresh->next = NULL;
	return (fresh);
}

void		ft_tube_lstadd(t_tube **list, char *room_a, char *room_b)
{
	t_tube	*tmp;

	if (*list)
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_tube_lstnew(room_a, room_b);
	}
	else
		list[0] = ft_tube_lstnew(room_a, room_b);
}

int			ft_tube_lstlen(t_tube *list)
{
	int		len;
	t_tube	*tmp;

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
