/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:52:22 by manki             #+#    #+#             */
/*   Updated: 2019/11/02 17:52:46 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	print_sol(t_room **tmp, int *i, int c_ants)
{
	if (tmp[*i])
	{
		ft_printf("L%d-%s", *i + 1, tmp[*i]->name);
	}
	if (*i < c_ants)
		*i = *i + 1;
}

int		already_pass(t_room **tmp, int i)
{
	int		o;
	t_room	*end;

	if (!tmp[i])
		return (-1);
	end = ft_get_room(&tmp[i], CMD_END);
	o = 0;
	while (o < i)
	{
		if (tmp[o] && tmp[i] && tmp[o] == tmp[i] && tmp[i] != end)
			return (1);
		o++;
	}
	return (-1);
}

void	tmp_next_child(t_room **tmp, int i)
{
	int		o;

	o = 0;
	while (o < i)
	{
		if (tmp[o])
			tmp[o] = tmp[o]->child;
		o++;
	}
}
