/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:27:37 by manki             #+#    #+#             */
/*   Updated: 2019/09/06 16:13:11 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

char			ft_check_map(char *input, char line_id, t_all *map)
{
	if (line_id == NUMBER && map->ants < 0)
		map->ants = ft_atoi(input);
	else if (line_id == ROOM && map->ants > 0 && !map->tube)
		return (ft_stock_room(input, &map->room));
	else if (line_id == TUBE && map->ants > 0 && map->room != NULL)
		return (ft_stock_tube(input, &map));
	else if (line_id != COMMENT && line_id != COMMAND)
		return (ERROR);
	return (1);
}
