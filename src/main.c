/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:09:18 by manki             #+#    #+#             */
/*   Updated: 2019/09/06 15:45:46 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		main(void)
{
	char	*input;
	t_all	all;

	all.room = NULL;
	all.tube = NULL;
	all.ants = -1;
	while (get_next_line(0, &input) == 1)
	{
		if (!ft_check_map(input, ft_check_line(input), &all))
			ft_error("ERROR", 2);
		ft_strdel(&input);
	}
	ft_display_all(&all);
	free_all(&all);
	return (0);
}
