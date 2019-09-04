/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:09:18 by manki             #+#    #+#             */
/*   Updated: 2019/09/04 12:58:13 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		main(void)
{
	char	*input;
	t_all	all;

	all.room = NULL;
	while (get_next_line(0, &input) == 1)
	{
		if (!ft_check_line(input))
			ft_error("ERROR", 2);
		stock_room(input, all.room);
//		ft_stock_input();
		ft_strdel(&input);
	}
	print_room_name(all.room);
	return (0);
}
